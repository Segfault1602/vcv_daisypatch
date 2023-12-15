# Daisy Patch for VCV Rack

## What it is
VcvDaisyPatch is a VCV Rack module that mimics the inputs and outputs of the Electro-Smith Daisy Patch. It allows easy testing of patches in VCV Rack before uploading to the Daisy Patch hardware. The aspiration for this project is to be able to simply copy and paste your `AudioCallback` code from your Daisy Patch project into the VcvDaisyPatch module and have it work without modification.

## What it isn't
VcvDaisyPatch is not an emulator of the Daisy Patch hardware. If the module you are working on uses any of the Daisy Patch hardware features like GPIOs, external SDRAM or other peripherals, you will need to find a way to abstract those features in your code so that they can be tested in VCV Rack.

## How to build
Follow the instructions for building VCV Rack plugins on the [VCV Rack website](https://vcvrack.com/manual/PluginDevelopmentTutorial.html). You will need to have the VCV Rack SDK installed and the `RACK_DIR` environment variable set to the location of the SDK.

Once your environment is set up, you can simply follow the VCV Rack instructions to build the plugin.