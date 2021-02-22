#include "HeterogeneousNode.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QDebug>

HeterogeneousNode::HeterogeneousNode(HeterogeneousType data, std::shared_ptr<HeterogeneousNode> parent/* = nullptr*/):
    ItemData(data),
    Parent(parent)
{

}

HeterogeneousNode::~HeterogeneousNode()
{

}

void HeterogeneousNode::SetParent(std::shared_ptr<HeterogeneousNode> parent)
{
    if(Parent == parent)
        return;

    Parent = parent;

    if (Parent)
        Parent->AddChild(shared_from_this());
}

void HeterogeneousNode::AddChild(std::shared_ptr<HeterogeneousNode> child)
{
    auto pair_res = Childs.insert(child);

    if (pair_res.second)
        child->SetParent(shared_from_this());
}

QString HeterogeneousNode::ToJson() const
{
    QString json_data = "{";

    json_data.append(ValueStr);
    json_data.append(": ");

    json_data.append(ItemData.toString());
    json_data.append(',');

    json_data.append(ChildsStr);
    json_data.append(": [");
    if (!Childs.empty())
    {
        for (auto it = Childs.begin(); it != Childs.end(); it++)
        {
           json_data.append((*it)->ToJson());
           json_data += ", ";
        }
    }

    json_data.append("]}");

    return json_data;
}

std::shared_ptr<HeterogeneousNode> HeterogeneousNode::FromJson(QString data)
{
     data.remove(' ');

    int curly_brace_count = 0;
    size_t index = 0;

    if (data[index] != '{')
        return std::shared_ptr<HeterogeneousNode>();

    curly_brace_count++;
    index++;

    size_t index_twoh = data.indexOf(':', index);
    QString value_str = data.mid(index, index_twoh - index);

    if (value_str != ValueStr)
        return std::shared_ptr<HeterogeneousNode>();

    index = index_twoh + 1;
    index_twoh = data.indexOf(',', index);
    value_str = data.mid(index, index_twoh - index);
    QVariant value = GetValueFromStr(value_str);
    index = index_twoh + 1;

    if (data[index] == '}')
        return std::make_shared<HeterogeneousNode>(HeterogeneousNode(value));

    std::shared_ptr<HeterogeneousNode> node = std::make_shared<HeterogeneousNode>(value);
    index_twoh = data.indexOf(':', index);

    if (index_twoh == -1)
        return std::shared_ptr<HeterogeneousNode>();

    value_str = data.mid(index, index_twoh - index);

    if (value_str != ChildsStr)
        return std::shared_ptr<HeterogeneousNode>();

    index = index_twoh + 1;
    size_t square_brackets = 0;

    if (data[index] != '[' || data.indexOf(']', index) ==-1)
        return std::shared_ptr<HeterogeneousNode>();

    if (data.indexOf(']', index) - index < 2)
        return node;

    index++;
    square_brackets++;

    QString sub_str;
    size_t child_brackets = 0;
    index_twoh = index;

    while (square_brackets && index_twoh < data.length() )
    {
        if (data[index_twoh] == '{')
        {
            if (!child_brackets)
                index = index_twoh;

            child_brackets++;
        }
        else if (data[index_twoh] == '}')
        {
            child_brackets--;

            if (!child_brackets)
            {
                sub_str = data.mid(index,  index_twoh - index + 1);
                node->AddChild(HeterogeneousNode::FromJson(sub_str));
                index_twoh += 2;
                index = index_twoh;
                continue;
            }
        }
        else if(data[index_twoh] == '[')
        {
            square_brackets++;
        }
        else if (data[index_twoh] == ']')
        {
            square_brackets--;
        }

        index_twoh++;
    }

    index_twoh++;

    if (data[index_twoh] != '}')
        return std::shared_ptr<HeterogeneousNode>();

    curly_brace_count--;

    if (square_brackets != 0 || curly_brace_count != 0)
        return std::shared_ptr<HeterogeneousNode>();

    return node;
}

QVariant HeterogeneousNode::GetValueFromStr(const QString& value)
{
    bool ok;
    float float_value = value.toFloat(&ok);

    if (ok)
    {
        int int_value = value.toInt(&ok);
        if (ok && float_value - int_value == 0)
            return int_value;

        return float_value;
    }

    return value;
}
