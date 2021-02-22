#ifndef HETEROGENEOUSNODE_H
#define HETEROGENEOUSNODE_H

#include <QVariant>
#include <string>
#include <set>
#include <memory>

using HeterogeneousType = QVariant;

const QString ValueStr = QStringLiteral("\"value\"");
const QString ChildsStr = QStringLiteral("\"childs\"");

class HeterogeneousNode: public std::enable_shared_from_this<HeterogeneousNode>
{
public:
    HeterogeneousNode(HeterogeneousType data, std::shared_ptr<HeterogeneousNode> parent = nullptr);
    ~HeterogeneousNode();

    void SetParent(std::shared_ptr<HeterogeneousNode> parent);
    std::shared_ptr<HeterogeneousNode> GetParent();
    void AddChild(std::shared_ptr<HeterogeneousNode> child);
    QString ToJson() const;
    static std::shared_ptr<HeterogeneousNode> FromJson(QString data);
    static QVariant GetValueFromStr(const QString& value);

private:
    HeterogeneousType ItemData;
    std::shared_ptr<HeterogeneousNode> Parent;
    std::set<std::shared_ptr<HeterogeneousNode>> Childs;
};

#endif // HETEROGENEOUSNODE_H
