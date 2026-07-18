#pragma once

#include "CombiningNode.hpp"

namespace nn {

// concatenate outputs of two nodes
class ConcatenationNode : public ICombiningNode
{
public:
    ConcatenationNode(const NodePtr& previousNodeA, const NodePtr& previousNodeB);
    virtual void Run(INodeContext& ctx) const override;
    virtual void Backpropagate(const Values& error, INodeContext& ctx, Gradients& gradients) const override;
};

} // namespace nn
