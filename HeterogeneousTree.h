#ifndef HETEROGENEOUSTREE_H
#define HETEROGENEOUSTREE_H

#include <HeterogeneousNode.h>


class HeterogeneousTree
{
public:
    HeterogeneousTree(std::shared_ptr<HeterogeneousNode> root_item);
    ~HeterogeneousTree();
    static std::shared_ptr<HeterogeneousTree> FromJson(const QString& data);
    QString ToJson() const;
    void SetRootItem(std::shared_ptr<HeterogeneousNode> root_item);

private:
    std::shared_ptr<HeterogeneousNode> RootItem;
};

#endif // HETEROGENEOUSTREE_H
