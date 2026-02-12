/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 31-01-2018
    License: MIT
*/

#include "../Stdinclude.hpp"

namespace Backend
{
    namespace Quest
    {
        std::unordered_map<uint32_t, bool> *Questmap;

        void Notifyassignment(uint32_t QuestID, uint32_t ActionID)
        {
            MQEL_json Notification = MQEL_json::object();
            Notification["$type"] = "HyperQuest.GameServer.Contracts.ServerAssignmentActionCompletedNotification, HyperQuest.GameServer.Contracts";
            Notification["AssignmentId"] = QuestID;
            Notification["AssignmentActionIndex"] = ActionID;
            Notification["NotificationType"] = 74;
            Backend::Notification::Enqueuelocal(Notification);
        }

        void Start(uint32_t QuestID) { Infoprint(va("Client started quest %i", QuestID)); (*Questmap)[QuestID] = false; }
        void Complete(uint32_t QuestID) { Infoprint(va("Client completed quest %i", QuestID)); (*Questmap)[QuestID] = true; }
        std::vector<uint32_t> Getcompleted()
        {
            std::vector<uint32_t> Result;
            for (auto &Item : *Questmap) if (Item.second) Result.push_back(Item.first);
            return Result;
        }
        void Update(uint32_t QuestID, uint32_t ActionID)
        {
            Infoprint(va("Client modified quest %i with action %i", QuestID, ActionID));
            Notifyassignment(QuestID, ActionID);
        }

        void Savequests()
        {
            Bytebuffer Writer;
            for (auto &Item : *Questmap) { Writer.Write(Item.first); Writer.Write(Item.second); }
            std::string Buffer((char *)Writer.Data(), Writer.Size());
            Package::Write("Quests.BB", Buffer);
        }
        void Loadquests()
        {
            if (Questmap == nullptr) Questmap = new std::unordered_map<uint32_t, bool>();
            std::atexit(Savequests);
            auto Filebuffer = Package::Read("Quests.BB");
            if (Filebuffer.size() == 0) return;
            Bytebuffer Reader(Filebuffer);
            while (true)
            {
                uint32_t QuestID; bool Status;
                if (!Reader.Read(QuestID)) break;
                if (!Reader.Read(Status)) break;
                (*Questmap)[QuestID] = Status;
            }
        }
        namespace { struct Startup { Startup() { Loadquests(); }; }; static Startup Loader{}; }
    }
}
