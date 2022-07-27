#! /usr/bin/env python
#
# Copyright 2021 Spotify AB
#
# Licensed under the GNU Public License, Version 3.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    https://www.gnu.org/licenses/gpl-3.0.html
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

try:
    from pedalboard_native import *  # noqa: F403, F401
except ImportError as _e:
    if "DLL load failed" in str(_e):
        # On Windows, we get an obtuse "DLL load failed" if the
        # MSVC++ redistributable library isn't installed
        raise ImportError(
            "Pedalboard failed to load its native code. Hint: try installing the Microsoft Visual"
            " C++ Redistributable."
        )
    else:
        raise
from pedalboard_native.utils import *  # noqa: F403, F401
from .pedalboard import Pedalboard, _AVAILABLE_PLUGIN_CLASSES, load_plugin  # noqa: F401
from .version import __version__  # noqa: F401

for _klass in _AVAILABLE_PLUGIN_CLASSES:
    vars()[_klass.__name__] = _klass
