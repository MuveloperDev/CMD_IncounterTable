#include <functional>
#include <vector>
#include <memory>

struct Action {
    std::function<void()> func;
};

typedef std::shared_ptr<Action> ActionPtr;

class Delegate {
public:
    void Add(const ActionPtr& action);
    void Remove(const ActionPtr& action);
    void Invoke();

private:
    std::vector<ActionPtr> actions;
};

