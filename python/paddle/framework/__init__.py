#   Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# TODO: import framework api under this directory 
__all__ = [
    'default_main_program', 'default_startup_program', 'create_global_var',
    'create_parameter', 'ParamAttr', 'Program', 'Variable', 'CPUPlace',
    'CUDAPlace', 'CUDAPinnedPlace'
]

__all__ += [
    'BackwardStrategy', 'grad', 'LayerList', 'load', 'save', 'prepare_context',
    'to_variable', 'no_grad', 'ParallelEnv', 'DataParallel', 'jit'
]

__all__ += [
    'NoamDecay', 'PiecewiseDecay', 'NaturalExpDecay', 'ExponentialDecay',
    'InverseTimeDecay', 'PolynomialDecay', 'CosineDecay'
]

from . import random
from .random import manual_seed
from ..fluid.framework import default_main_program, default_startup_program, Program, Variable
from ..fluid.param_attr import ParamAttr
from ..fluid.layers.tensor import create_global_var, create_parameter
from ..fluid.core import CPUPlace, CUDAPlace, CUDAPinnedPlace

from paddle.fluid import core
from ..fluid.dygraph.base import no_grad, to_variable, grad
from ..fluid.dygraph.checkpoint import load_dygraph as load
from ..fluid.dygraph.checkpoint import save_dygraph as save
from ..fluid.dygraph.parallel import prepare_context, ParallelEnv, DataParallel

from . import jit

from ..fluid.dygraph.learning_rate_scheduler import NoamDecay, PiecewiseDecay, NaturalExpDecay, ExponentialDecay, \
        InverseTimeDecay, PolynomialDecay, CosineDecay

BackwardStrategy = core.BackwardStrategy
