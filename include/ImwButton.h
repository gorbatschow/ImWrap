#pragma once
#include "ImwBasicElement.h"

namespace Imw {
class Button : public BasicElement {
public:
  Button(const std::string &label = {}) : BasicElement(label) {
    _width = 50.0f;
  }

  virtual ~Button() override = default;

  virtual bool handle() override {
    const bool trig = _triggered;
    _triggered = false;
    return trig;
  }

protected:
  virtual void paintElement() override {
    if (std::isnan(_width)) {
      _triggered = ImGui::Button(_label.c_str());
    } else {
      _triggered = ImGui::Button(_label.c_str(), {_width, 0.0f});
    }
  }

  bool _triggered{false};
};
} // namespace Imw
