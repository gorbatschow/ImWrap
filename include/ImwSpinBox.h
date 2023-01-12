#pragma once
#include "ImwValueElement.h"

namespace Imw {
template <typename T> class SpinBox : public ValueElement<T> {
  using Base = ValueElement<T>;

public:
  // Constructor
  SpinBox(const std::string &label = {}) : Base(label) { SpinBoxImpl(); }

  // Destructor
  virtual ~SpinBox() override = default;

  // Set Value
  virtual void setValue(const T &value, int index = 0) override {
    Base::setValue(std::clamp(value, _valueLimits.first, _valueLimits.second));
  }

  // Set Value Step
  virtual void setValueStep(const T &step, int index = 0) override {
    _valueStep = step;
  }

  // Set Value Fast Step
  virtual void setValueFastStep(const T &fstep, int index = 0) override {
    _valueFastStep = fstep;
  }

  // Set Value Limits
  virtual void setValueLimits(const std::pair<T, T> &limits,
                              int index = 0) override {
    _valueLimits = limits;
    setValue(Base::currentValue());
  }

protected:
  // Paint Element
  virtual void paintElement() override { paintElementImpl(); }
  void paintElementImpl() {}
  void SpinBoxImpl() {}

  T _valueStep{};
  T _valueFastStep{};
  std::pair<T, T> _valueLimits{std::numeric_limits<T>::min() / T(2),
                               std::numeric_limits<T>::max() / T(2)};
};

// SpinBox<int>
// -----------------------------------------------------------------------------

template <> inline void SpinBox<int>::SpinBoxImpl() {
  _textFormat = "%d";
  _valueStep = 1;
  _valueFastStep = 10;
}

template <> inline void SpinBox<int>::paintElementImpl() {
  int value{_value};
  _changed =
      ImGui::InputInt(_label.c_str(), &value, _valueStep, _valueFastStep);
  if (_changed) {
    setValue(value);
  }
}

// SpinBox<float>
// -----------------------------------------------------------------------------

template <> inline void SpinBox<float>::SpinBoxImpl() {
  _textFormat = "%.2f";
  _valueStep = 0.1f;
  _valueFastStep = 10.0f;
}

template <> inline void SpinBox<float>::paintElementImpl() {
  float value{_value};
  _changed = ImGui::InputFloat(_label.c_str(), &value, _valueStep,
                               _valueFastStep, _textFormat.c_str());
  if (_changed) {
    setValue(value);
  }
}

} // namespace Imw
