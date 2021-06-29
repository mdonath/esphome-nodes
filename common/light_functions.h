void dim_relative(LightState *lightState, float value) {
    auto call = lightState->make_call();
    float cur;
    lightState->remote_values.as_brightness(&cur);
    float new_brightness = clamp(cur + value, 0.0f, 1.0f);
    call.set_state(new_brightness != 0.0f);
    call.set_brightness(new_brightness);
    call.perform();
}

void set_color(LightState *lightState, float r, float g, float b) {
    auto call = lightState->make_call();
    call.set_rgb(r, g, b);
    call.perform();
}

void set_effect(LightState *lightState, const std::string &effect) {
    auto call = lightState->turn_on();
    call.set_effect(effect);
    call.perform();
}
