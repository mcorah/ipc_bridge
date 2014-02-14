% Copyright (c) 2014, Nathan Michael
% All rights reserved.

% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions are met:

% 1. Redistributions of source code must retain the above copyright notice, this
% list of conditions and the following disclaimer.

% 2. Redistributions in binary form must reproduce the above copyright notice,
% this list of conditions and the following disclaimer in the documentation
% and/or other materials provided with the distribution.

% 3. Neither the name of the copyright holder nor the names of its contributors
% may be used to endorse or promote products derived from this software without
% specific prior written permission.

% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
% AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
% IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
% DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
% FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
% DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
% SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
% CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
% OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
% OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

classdef ipc_ros < handle
    properties;
        bridge
        name
        mode
        pid
        connected
    end

    methods;
        function obj = ipc_ros()
            obj.connected = false;
        end

        function create(obj, type_, name_, mode_)
            obj.bridge = str2func(type_);
            try
                msg = obj.bridge('empty');
            catch
                error(sprintf('ipc_ros (%s): failed to construct bridge', type_));
                return;
            end

            obj.name = name_;
            if strcmp('publisher', mode_)
                obj.mode = 'publisher';
            elseif strcmp('subscriber', mode_)
                obj.mode = 'subscriber';
            else
                error('ipc_ros (%s): publisher or subscriber required', obj.name);
                return;
            end

            obj.connect();
        end

        function delete(obj)
            obj.disconnect();
        end

        function connect(obj)
            if ~obj.connected
                obj.pid = obj.bridge('connect', obj.mode, obj.name, obj.name);
            end

            if obj.pid == -1
                error('ipc_ros (%s): failed to connect', obj.name);
            else
                obj.connected = true;
            end
        end

        function disconnect(obj)
            if obj.connected
                obj.bridge('disconnect', obj.pid);
            end
            obj.connected = false;
            obj.pid = [];
        end
    end
end
