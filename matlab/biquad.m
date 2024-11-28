classdef biquad < audioPlugin

    properties % parameters & their default values
        HS_FREQ = 15000;      
        HS_GAIN = 0;
        HS_Q = 0.5;
        
        HMF_FREQ = 8000;
        HMF_GAIN = 0;
        HMF_Q = 0.5;
        
        LMF_FREQ = 500;
        LMF_GAIN = 0;
        LMF_Q = 0.5;
        
        HPF_FREQ = 30;
        HPF_Q = 0.5;

        LPF_FREQ = 18000;
        LPF_Q = 0.5;
        
        fs = getSampleRate(audioPlugin);
        fn = 22050;
        
        typeHMF = 'Band';
        typeLMF = 'Band';

        BYPASS_BIQUAD = 'off';
    end

    properties (Constant)
        PluginInterface = audioPluginInterface(...
            'PluginName', 'Biquad',...
            'VendorName', 'Amari Stewart',...
            'VendorVersion', '1.0.0',...
            'UniqueId', 'AAS3',...
            'BackgroundImage', 'Equalizer.png',...
             audioPluginGridLayout(...
                'RowHeight', [25 85 25 25 85 25 85 25 85 25],...
                'ColumnWidth', [25 85 85 85 85 85 85 85 85 85 25]), ...
          audioPluginParameter('HS_FREQ',...
            'DisplayName','HI SHLF',...
            'Label', 'Hz',...
            'Mapping',{'log',1000,20000},...
            'Style', 'rotaryknob',...
            'Layout', [5,8],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('HS_Q',...
            'DisplayName','Q',...
            'Mapping',{'log',0.1,10},...
            'Style', 'rotaryknob',...
            'Layout', [7,8],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('HS_GAIN',...
            'DisplayName','GAIN',...
            'Label', 'dB',...
            'Mapping',{'lin',-12,12},...
            'Style', 'rotaryknob',...
            'Layout', [9,8],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('HMF_FREQ',...
            'DisplayName','HI-MID',...
            'Label', 'Hz',...
            'Mapping',{'log',8000,12500},...
            'Style', 'rotaryknob',...
            'Layout', [5,6],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('HMF_Q',...
            'DisplayName','Q',...
            'Mapping',{'log',0.1,10},...
            'Style', 'rotaryknob',...
            'Layout', [7,6],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('HMF_GAIN',...
            'DisplayName','GAIN',...
            'Label', 'dB',...
            'Mapping',{'lin',-12,12},...
            'Style', 'rotaryknob',...
            'Layout', [9,6],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('LMF_FREQ',...
            'DisplayName','LO-MID',...
            'Label', 'Hz',...
            'Mapping',{'log',200,8000},...
            'Style', 'rotaryknob',...
            'Layout', [5,4],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('LMF_Q',...
            'DisplayName','Q',...
            'Mapping',{'log',0.1,10},...
            'Style', 'rotaryknob',...
            'Layout', [7,4],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('LMF_GAIN',...
            'DisplayName','GAIN',...
            'Label', 'dB',...
            'Mapping',{'lin',-12,12},...
            'Style', 'rotaryknob',...
            'Layout', [9,4],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('HPF_FREQ',...
            'DisplayName','HPF',...
            'Label', 'Hz',...
            'Mapping',{'log',20,400},...
            'Style', 'rotaryknob',...
            'Layout', [5,2],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('HPF_Q',...
            'DisplayName','Q',...
            'Mapping',{'log',0.1,10},...
            'Style', 'rotaryknob',...
            'Layout', [7,2],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('LPF_FREQ',...
            'DisplayName','LPF',...
            'Label', 'Hz',...
            'Mapping',{'log',2500,20000},...
            'Style', 'rotaryknob',...
            'Layout', [5,10],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('LPF_Q',...
            'DisplayName','Q',...
            'Mapping',{'log',0.1,10},...
            'Style', 'rotaryknob',...
            'Layout', [7,10],...
            'DisplayNameLocation', 'above',...
            'Filmstrip', 'Vintage_Knob.png',...
            'FilmstripFrameSize', [64 64]), ...
          audioPluginParameter('typeHMF',...
            'Style', 'dropdown',...
            'DisplayNameLocation','none', ...
            'Mapping', {'enum', 'Band', 'Peaking','Notch'},...
            'Layout', [3,6],...
            'Filmstrip', 'switch_metal.png',...
            'FilmstripFrameSize', [64 64]),...
          audioPluginParameter('typeLMF',...
            'Style', 'dropdown',...
            'DisplayNameLocation','none', ...
            'Mapping', {'enum', 'Band', 'Peaking','Notch'},...
            'Layout', [3,4],...
            'Filmstrip', 'switch_metal.png',...
            'FilmstripFrameSize', [64 64]),...
          audioPluginParameter('BYPASS_BIQUAD',...
            'Style', 'vrocker',...
            'DisplayNameLocation','none', ...
            'Mapping', {'enum', 'off', 'on'},...
            'Layout', [2,8],...
            'Filmstrip', 'switch_metal.png',...
            'FilmstripFrameSize', [64 64])...
          );
    end

    properties (Access = private) % saves filter states in w, two for left and right channels
        filter_HS = struct('w', [0 0; 0 0], 'a0', 1, 'a1', 0, 'a2', 0, 'b0', 1, 'b1', 0, 'b2', 0);
        filter_HMF = struct('w', [0 0; 0 0], 'a0', 1, 'a1', 0, 'a2', 0, 'b0', 1, 'b1', 0, 'b2', 0);     
        filter_LMF = struct('w', [0 0; 0 0], 'a0', 1, 'a1', 0, 'a2', 0, 'b0', 1, 'b1', 0, 'b2', 0);
        filter_HPF = struct('w', [0 0; 0 0], 'a0', 1, 'a1', 0, 'a2', 0, 'b0', 1, 'b1', 0, 'b2', 0);
        filter_LPF = struct('w', [0 0; 0 0], 'a0', 1, 'a1', 0, 'a2', 0, 'b0', 1, 'b1', 0, 'b2', 0);

        compressor;

        % parameter smoothers
        hsFreqSmoother
        hmfFreqSmoother
        lmfFreqSmoother
        hpfFreqSmoother
        lpfFreqSmoother

        hsGainSmoother
        hmfGainSmoother
        lmfGainSmoother
        
        hsQSmoother
        hmfQSmoother
        lmfQSmoother
        hpfQSmoother
        lpfQSmoother
       
    end
    
    methods
        function plugin = biquad()
            % Initialize smoothers with default values
            plugin.hsFreqSmoother = ParameterSmoother(plugin.HS_FREQ, 0.9);
            plugin.hmfFreqSmoother = ParameterSmoother(plugin.HMF_FREQ, 0.9);
            plugin.lmfFreqSmoother = ParameterSmoother(plugin.LMF_FREQ, 0.9);
            plugin.hpfFreqSmoother = ParameterSmoother(plugin.HPF_FREQ, 0.9);
            plugin.lpfFreqSmoother = ParameterSmoother(plugin.LPF_FREQ, 0.9);

            plugin.hsGainSmoother = ParameterSmoother(plugin.HS_GAIN, 0.9);
            plugin.hmfGainSmoother = ParameterSmoother(plugin.HMF_GAIN, 0.9);
            plugin.lmfGainSmoother = ParameterSmoother(plugin.LMF_GAIN, 0.9);

            plugin.hsQSmoother = ParameterSmoother(plugin.HS_Q, 0.9);
            plugin.hmfQSmoother = ParameterSmoother(plugin.HMF_Q, 0.9);
            plugin.lmfQSmoother = ParameterSmoother(plugin.LMF_Q, 0.9);
            plugin.hpfQSmoother = ParameterSmoother(plugin.HPF_Q, 0.9);
            plugin.lpfQSmoother = ParameterSmoother(plugin.LPF_Q, 0.9);
        end

        function out = process(plugin,in)
            
            out1 = coder.nullcopy(zeros(size(in)));
            out = coder.nullcopy(zeros(size(in)));

            % Smooth values
            update_HMF(plugin);
            update_LMF(plugin);
            update_HPF(plugin);
            update_LPF(plugin);
            update_HS(plugin);
            
            for ch = 1:min(size(in)) % iterates over # of channels on the input
       
                x = in(:,ch); % creates pointer to channel

                [x, plugin.filter_HS.w(:,ch)] = processBiquad(x, plugin.filter_HS, ch); % passes the filter object containing filter state and filter coeffiecients
                [x, plugin.filter_HMF.w(:,ch)] = processBiquad(x, plugin.filter_HMF, ch); 
                [x, plugin.filter_LMF.w(:,ch)] = processBiquad(x, plugin.filter_LMF, ch);
                [x, plugin.filter_HPF.w(:,ch)] = processBiquad(x, plugin.filter_HPF, ch);
                [x, plugin.filter_LPF.w(:,ch)] = processBiquad(x, plugin.filter_LPF, ch);

                if strcmp(plugin.BYPASS_BIQUAD,'on')
                    out1(:,ch)= in(:,ch);
                else
                    out1(:,ch) = x; 
                end

            end
            
            out(:,:) = out1(:,:);

        end
        
        function reset(plugin)
            
            plugin.fs = getSampleRate(plugin);
            plugin.fn = plugin.fs/2;
            
            plugin.filter_HS.w = [0 0; 0 0];

            plugin.filter_HMF.w = [0 0; 0 0];
 
            plugin.filter_LMF.w = [0 0; 0 0];

            plugin.filter_HPF.w = [0 0; 0 0];

            plugin.filter_LPF.w = [0 0; 0 0];
            
        end
        
        function set.HS_FREQ(plugin, val)
            plugin.HS_FREQ = val;
            plugin.hsFreqSmoother.setTargetValue(val);
        end
        
        function set.HS_GAIN(plugin, val)
            plugin.HS_GAIN = val;
            plugin.hsGainSmoother.setTargetValue(val);
        end

        function set.HS_Q(plugin, val)
            plugin.HS_Q = val;
            plugin.hsQSmoother.setTargetValue(val);
        end
        
        function update_HS(plugin)
            f0 = plugin.hsFreqSmoother.step();
            Q = plugin.hsQSmoother.step();
            gain = plugin.hsGainSmoother.step();
            w0 = 2*pi*f0/plugin.fs;
            alpha = sin(w0)/(2*Q);
            %A = sqrt(db2mag(gain));
            A = 10^(gain/40);
            
            if abs(gain) < 0.001
                plugin.filter_HS.a0 = 1;
                plugin.filter_HS.a1 = 0;
                plugin.filter_HS.a2 = 0;
                plugin.filter_HS.b0 = 1;
                plugin.filter_HS.b1 = 0;
                plugin.filter_HS.b2 = 0;
                return;
            end

            plugin.filter_HS.a0 =    A*( (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha ); 
            plugin.filter_HS.a1 = -2*A*( (A-1) + (A+1)*cos(w0)                   );
            plugin.filter_HS.a2 =    A*( (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha );
            plugin.filter_HS.b0 =        (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha;
            plugin.filter_HS.b1 =    2*( (A-1) - (A+1)*cos(w0)                   );
            plugin.filter_HS.b2 =        (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha;

        end
        
        function set.HMF_FREQ(plugin, val)
            plugin.HMF_FREQ = val;
            plugin.hmfFreqSmoother.setTargetValue(val);

        end
        
        function set.HMF_GAIN(plugin, val)
            plugin.HMF_GAIN = val;
            plugin.hmfGainSmoother.setTargetValue(val);
        end
        
        function set.HMF_Q(plugin, val)
            plugin.HMF_Q = val;
            plugin.hmfQSmoother.setTargetValue(val);
        end

        function update_HMF(plugin)

            Q = plugin.hmfQSmoother.step();
            f0 = plugin.hmfFreqSmoother.step();
            gain = plugin.hmfGainSmoother.step();
            w0 = 2*pi*f0/plugin.fs;
            alpha = sin(w0)/(2*Q);
            %A = sqrt(db2mag(gain));
            A = 10^(gain/40);
            
            if abs(gain) < 0.001
                plugin.filter_HMF.a0 = 1;
                plugin.filter_HMF.a1 = 0;
                plugin.filter_HMF.a2 = 0;
                plugin.filter_HMF.b0 = 1;
                plugin.filter_HMF.b1 = 0;
                plugin.filter_HMF.b2 = 0;
                return;
            end

            if strcmp(plugin.typeHMF,'Band')
                plugin.filter_HMF.a0 =   alpha*A;
                plugin.filter_HMF.a1 =   0;
                plugin.filter_HMF.a2 =   -alpha*A;
                plugin.filter_HMF.b0 =   1 + alpha;
                plugin.filter_HMF.b1 =  -2*cos(w0);
                plugin.filter_HMF.b2 =   1 - alpha;
            elseif strcmp(plugin.typeHMF,'Peaking')
                plugin.filter_HMF.a0 =   1 + alpha*A;
                plugin.filter_HMF.a1 =  -2*cos(w0);
                plugin.filter_HMF.a2 =   1 - alpha*A;
                plugin.filter_HMF.b0 =   1 + alpha/A;
                plugin.filter_HMF.b1 =  -2*cos(w0);
                plugin.filter_HMF.b2 =   1 - alpha/A;
            elseif strcmp(plugin.typeHMF,'Notch')
                plugin.filter_HMF.a0 =   1;
                plugin.filter_HMF.a1 =  -2*cos(w0);
                plugin.filter_HMF.a2 =   1;
                plugin.filter_HMF.b0 =   1 + alpha;
                plugin.filter_HMF.b1 =  -2*cos(w0);
                plugin.filter_HMF.b2 =   1 - alpha;
            end

        end
        
        function set.LMF_FREQ(plugin, val)
            plugin.LMF_FREQ = val;
            plugin.lmfFreqSmoother.setTargetValue(val);
        end
        
        function set.LMF_GAIN(plugin, val)
            plugin.LMF_GAIN = val;
            plugin.lmfGainSmoother.setTargetValue(val);
        end

        function set.LMF_Q(plugin, val)
            plugin.LMF_Q = val;
            plugin.lmfQSmoother.setTargetValue(val);
        end
        
        function update_LMF(plugin)

            Q = plugin.lmfQSmoother.step();
            f0 = plugin.lmfFreqSmoother.step();
            gain = plugin.lmfGainSmoother.step();
            w0 = 2*pi*f0/plugin.fs;
            alpha = sin(w0)/(2*Q);
            %A = sqrt(db2mag(gain));
            A = 10^(gain/40);

            if abs(gain) < 0.001
                plugin.filter_LMF.a0 = 1;
                plugin.filter_LMF.a1 = 0;
                plugin.filter_LMF.a2 = 0;
                plugin.filter_LMF.b0 = 1;
                plugin.filter_LMF.b1 = 0;
                plugin.filter_LMF.b2 = 0;
                return;
            end
            
            if strcmp(plugin.typeLMF,'Band')
                plugin.filter_LMF.a0 =   alpha*A;
                plugin.filter_LMF.a1 =   0;
                plugin.filter_LMF.a2 =   -alpha*A;
                plugin.filter_LMF.b0 =   1 + alpha;
                plugin.filter_LMF.b1 =  -2*cos(w0);
                plugin.filter_LMF.b2 =   1 - alpha;
            elseif strcmp(plugin.typeLMF,'Peaking')
                plugin.filter_LMF.a0 =   1 + alpha*A;
                plugin.filter_LMF.a1 =  -2*cos(w0);
                plugin.filter_LMF.a2 =   1 - alpha*A;
                plugin.filter_LMF.b0 =   1 + alpha/A;
                plugin.filter_LMF.b1 =  -2*cos(w0);
                plugin.filter_LMF.b2 =   1 - alpha/A;
            elseif strcmp(plugin.typeLMF,'Notch')
                plugin.filter_LMF.a0 =   1;
                plugin.filter_LMF.a1 =  -2*cos(w0);
                plugin.filter_LMF.a2 =   1;
                plugin.filter_LMF.b0 =   1 + alpha;
                plugin.filter_LMF.b1 =  -2*cos(w0);
                plugin.filter_LMF.b2 =   1 - alpha;
            end
        end
        
        
        function set.HPF_FREQ(plugin, val)
            plugin.HPF_FREQ = val;
            plugin.hpfFreqSmoother.setTargetValue(val);

        end

        function set.HPF_Q(plugin, val)
            plugin.HPF_Q = val;
            plugin.hpfQSmoother.setTargetValue(val);

        end

        function update_HPF(plugin)

            f0 = plugin.hpfFreqSmoother.step();
            Q = plugin.hpfQSmoother.step();
            w0 =2 *pi*f0/plugin.fs;
            alpha = sin(w0)/(2*Q);
          
            plugin.filter_HPF.a0 =  (1 + cos(w0))/2;
            plugin.filter_HPF.a1 = -(1 + cos(w0));
            plugin.filter_HPF.a2 =  (1 + cos(w0))/2;
            plugin.filter_HPF.b0 =   1 + alpha;
            plugin.filter_HPF.b1 =  -2*cos(w0);
            plugin.filter_HPF.b2 =   1 - alpha;

        end

        function set.LPF_FREQ(plugin, val)
            plugin.LPF_FREQ = val;
            plugin.lpfFreqSmoother.setTargetValue(val);
        end
        
        function set.LPF_Q(plugin, val)
            plugin.LPF_Q = val;
            plugin.lpfQSmoother.setTargetValue(val);
        end

        function update_LPF(plugin)

            f0 = plugin.lpfFreqSmoother.step();
            Q = plugin.lpfQSmoother.step();
            w0 = 2*pi*f0/plugin.fs;
            alpha = sin(w0)/(2*Q);
            
            plugin.filter_LPF.a0 =  (1 - cos(w0))/2;
            plugin.filter_LPF.a1 = 1 - cos(w0);
            plugin.filter_LPF.a2 =  (1 - cos(w0))/2;
            plugin.filter_LPF.b0 =   1 + alpha;
            plugin.filter_LPF.b1 =  -2*cos(w0);
            plugin.filter_LPF.b2 =   1 - alpha;

        end
        
        function set.BYPASS_BIQUAD(plugin, val)
            plugin.BYPASS_BIQUAD = val;
        end
        
    end

end