/* Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include <memory>
#include <string>
#include <vector>

#include "paddle/fluid/operators/npu_op_runner.h"
#include "paddle/fluid/operators/sum_op.h"

namespace paddle {
namespace operators {

using Tensor = framework::Tensor;

template <typename DeviceContext, typename T>
class SumNPUKernel : public framework::OpKernel<T> {
 public:
  void Compute(const framework::ExecutionContext& ctx) const override {
    auto x = ctx.MultiInput<Tensor>("X");
    auto* out = ctx.Output<Tensor>("Out");
    out->mutable_data<T>(ctx.GetPlace());

    auto place = ctx.GetPlace();

    int n = static_cast<int>(x.size());
    if (n == 1) {
      TensorCopy(*x[0], place, out);
      return;
    }

    std::vector<framework::Tensor> inputs;
    std::vector<std::string> names;
    for (int i = 0; i < n; ++i) {
      if (x[i] && x[i]->numel() > 0) {
        inputs.push_back(*x[i]);
        names.push_back("x" + std::to_string(i));
      } else {
        continue;
      }
    }

    auto stream =
        ctx.template device_context<paddle::platform::NPUDeviceContext>()
            .stream();
    NpuOpRunner runner{"AddN", {inputs}, {*out}, {{"N", n}}};
    runner.AddInputNames(names);
    runner.Run(stream);
  }
};

}  // namespace operators
}  // namespace paddle

namespace ops = paddle::operators;

REGISTER_OP_NPU_KERNEL(
    sum, ops::SumNPUKernel<paddle::platform::NPUDeviceContext, float>,
    ops::SumNPUKernel<paddle::platform::NPUDeviceContext,
                      paddle::platform::float16>);

