#pragma once
#include<stack>
#include<memory>
#include "State.hpp"
using namespace std;

namespace Engine{
    class StateManager{
        private:
            stack<unique_ptr<State>> m_stateStack;
            unique_ptr<State> m_newState;

            bool m_add;
            bool m_replace;
            bool m_remove;
        public:
            StateManager();
            ~StateManager();

            void Add(unique_ptr<State> toAdd, bool replace = false);
            void PopCurrent();
            void ProcessStateChanges();
            unique_ptr<State>& getCurrent();
    };
}
