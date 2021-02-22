#include "HeterogeneousTree.h"
#include "HeterogeneousNode.h"

HeterogeneousTree::HeterogeneousTree(std::shared_ptr<HeterogeneousNode> root_item):
    RootItem(root_item)
{

}

HeterogeneousTree::~HeterogeneousTree()
{

}

std::shared_ptr<HeterogeneousTree> HeterogeneousTree::FromJson(const QString& data)
{
    return std::make_shared<HeterogeneousTree>(HeterogeneousNode::FromJson(data));
}

QString HeterogeneousTree::ToJson() const
{
    if (!RootItem)
        return QString();

    return RootItem->ToJson();
}

void HeterogeneousTree::SetRootItem(std::shared_ptr<HeterogeneousNode> root_item)
{
    RootItem = root_item;
}
