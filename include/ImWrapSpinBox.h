#pragma once
#include "ImWrapValueElement.h"

namespace ImWrap {
template <typename T> class SpinBox : public ValueElement<T> {
  using Base = ValueElement<T>;
  static constexpr std::pair<int, int> DefaultLimits{
      std::numeric_limits<int>::min() / T{2},
      std::numeric_limits<int>::max() / T{2}};

public:
  // Constructor
  SpinBox(const std::string &label = {}, const T &value = {})
      : Base(label, value) {
    SpinBoxImpl();
  }

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
  std::pair<T, T> _valueLimits{DefaultLimits};
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
  const auto changed{
      ImGui::InputInt(_label.c_str(), &value, _valueStep, _valueFastStep)};
  if (changed) {
    setValue(value);
    trigger();
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
  const auto changed{ImGui::InputFloat(_label.c_str(), &value, _valueStep,
                                       _valueFastStep, _textFormat.c_str())};
  if (changed) {
    setValue(value);
    trigger();
  }
}

} // namespace ImWrap
