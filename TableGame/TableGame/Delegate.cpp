#include "Delegate.h"
#include <algorithm>

void Delegate::Add(const ActionPtr& action) {
    actions.push_back(action);
}

void Delegate::Remove(const ActionPtr& action) {
    actions.erase(std::remove(actions.begin(), actions.end(), action), actions.end());
}

void Delegate::Invoke() {
    for (const auto& action : actions) {
        action->func();
    }
}