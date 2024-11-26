classdef ParameterSmoother < matlab.System % MATLAB system object tm, used to eliminate abrupt chnages in parameters
    properties
        smoothingFactor = 0.99; % Smoothing factor (0 < smoothingFactor < 1)
    end
    
    properties (Access = private)
        currentValue
        targetValue
    end
    
    methods
        function obj = ParameterSmoother(initialValue, smoothingFactor) % constructor
            if nargin > 0
                obj.currentValue = initialValue; % gradually updated each time the audio frame is processed
                obj.targetValue = initialValue; % will incrementally adjust currentValue towards targetValue
                obj.smoothingFactor = smoothingFactor; % rate at which the currentValue approaches the targetValue
            end
        end
        
        function setTargetValue(obj, value) % setter
            obj.targetValue = value;
        end
    end
    methods(Access = protected)
        function smoothedValue = stepImpl(obj) % used to update parameter value incrementally each time the audio frame is processed
            % Perform the smoothing
            obj.currentValue = obj.smoothingFactor * obj.currentValue + ...
                               (1 - obj.smoothingFactor) * obj.targetValue; % larger smooth val = slower ramp, smaller smooth val = faster ramp
            smoothedValue = obj.currentValue;
        end
    end
end