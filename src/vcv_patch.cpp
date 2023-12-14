#include "plugin.hpp"

struct VcvPatch : Module
{
    enum ParamId
    {
        CTR1_PARAM,
        CTRL2_PARAM,
        CTRL3_PARAM,
        CTRL4_PARAM,
        ENC1_PARAM,
        PARAMS_LEN
    };
    enum InputId
    {
        CV_IN1_INPUT,
        CV_IN2_INPUT,
        CV_IN3_INPUT,
        CV_IN4_INPUT,
        GATE_IN_1_INPUT,
        GATE_IN_2_INPUT,
        IN_1_INPUT,
        IN_2_INPUT,
        IN_3_INPUT,
        IN_4_INPUT,
        MIDI_IN_INPUT,
        INPUTS_LEN
    };
    enum OutputId
    {
        GATE_OUT_OUTPUT,
        CV_OUT1_OUTPUT,
        OUT_1_OUTPUT,
        OUT_2_OUTPUT,
        OUT_3_OUTPUT,
        OUT_4_OUTPUT,
        MIDI_OUT_OUTPUT,
        CV_OUT2_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId
    {
        LIGHTS_LEN
    };

    VcvPatch()
    {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configParam(CTR1_PARAM, 0.f, 1.f, 0.f, "CTRL 1");
        configParam(CTRL2_PARAM, 0.f, 1.f, 0.f, "CTRL 2");
        configParam(CTRL3_PARAM, 0.f, 1.f, 0.f, "CTRL 3");
        configParam(CTRL4_PARAM, 0.f, 1.f, 0.f, "CTRL 4");
        configParam(ENC1_PARAM, -INFINITY, INFINITY, 0.f, "Encoder");
        configInput(CV_IN1_INPUT, "CV In 1");
        configInput(CV_IN2_INPUT, "CV In 2");
        configInput(CV_IN3_INPUT, "CV In 3");
        configInput(CV_IN4_INPUT, "CV In 4");
        configInput(GATE_IN_1_INPUT, "Gate In 1");
        configInput(GATE_IN_2_INPUT, "Gate In 2");
        configInput(IN_1_INPUT, "Audio In 1");
        configInput(IN_2_INPUT, "Audio In 2");
        configInput(IN_3_INPUT, "Audio In 3");
        configInput(IN_4_INPUT, "Audio In 4");
        configInput(MIDI_IN_INPUT, "MIDI In");
        configOutput(GATE_OUT_OUTPUT, "Gate Out");
        configOutput(CV_OUT1_OUTPUT, "CV Out 1");
        configOutput(CV_OUT2_OUTPUT, "CV Out 2");
        configOutput(OUT_1_OUTPUT, "Audio Out 1");
        configOutput(OUT_2_OUTPUT, "Audio Out 2");
        configOutput(OUT_3_OUTPUT, "Audio Out 3");
        configOutput(OUT_4_OUTPUT, "Audio Out 4");
        configOutput(MIDI_OUT_OUTPUT, "MIDI Out");
    }

    void process(const ProcessArgs &args) override
    {

        // simple passthrough
        outputs[OUT_1_OUTPUT].setVoltage(inputs[IN_1_INPUT].getVoltage());
        outputs[OUT_2_OUTPUT].setVoltage(inputs[IN_2_INPUT].getVoltage());
        outputs[OUT_3_OUTPUT].setVoltage(inputs[IN_3_INPUT].getVoltage());
        outputs[OUT_4_OUTPUT].setVoltage(inputs[IN_4_INPUT].getVoltage());
    }
};

struct DaisyDisplay : LedDisplay
{
    VcvPatch *module;

    void drawLayer(const DrawArgs &args, int layer) override
    {
        LedDisplay::drawLayer(args, layer);
    }
};

struct DaisyWidget : ModuleWidget
{
    DaisyWidget(VcvPatch *module)
    {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/daisy.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.449, 30.303)), module, VcvPatch::CTR1_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(34.131, 30.303)), module, VcvPatch::CTRL2_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(51.26, 30.303)), module, VcvPatch::CTRL3_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(68.335, 30.303)), module, VcvPatch::CTRL4_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(17.16, 60.176)), module, VcvPatch::ENC1_PARAM));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.653, 16.449)), module, VcvPatch::CV_IN1_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(30.8, 16.449)), module, VcvPatch::CV_IN2_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(51.223, 16.449)), module, VcvPatch::CV_IN3_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.426, 16.449)), module, VcvPatch::CV_IN4_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(89.862, 16.449)), module, VcvPatch::GATE_IN_1_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(89.862, 30.745)), module, VcvPatch::GATE_IN_2_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.229, 91.738)), module, VcvPatch::IN_1_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.133, 91.738)), module, VcvPatch::IN_2_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(29.924, 91.738)), module, VcvPatch::IN_3_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(41.715, 91.738)), module, VcvPatch::IN_4_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(53.731, 91.738)), module, VcvPatch::MIDI_IN_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(89.862, 45.704)), module, VcvPatch::GATE_OUT_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(65.747, 91.738)), module, VcvPatch::CV_OUT1_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.802, 106.752)), module, VcvPatch::OUT_1_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(17.786, 106.752)), module, VcvPatch::OUT_2_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(29.995, 106.752)), module, VcvPatch::OUT_3_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(42.204, 106.752)), module, VcvPatch::OUT_4_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.737, 106.752)), module, VcvPatch::MIDI_OUT_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(66.058, 106.752)), module, VcvPatch::CV_OUT2_OUTPUT));

        // LCD display
        DaisyDisplay *display = createWidget<DaisyDisplay>(mm2px(Vec(28.9719, 48.1542)));
        display->box.size = mm2px(Vec(38.894, 20.505));
        display->module = module;
        addChild(display);
    }
};

Model *modelDaisy = createModel<VcvPatch, DaisyWidget>("VcvDaisyPatch");