#pragma once
#include "ImwValueElement.h"

namespace Imw {
template <class T> class SpinBox : public ValueElement<T> {
public:
  // Constructor
  SpinBox(const std::string &label = {}) : ValueElement<T>(label) {
    SpinBoxImpl();
  }

  // Destructor
  virtual ~SpinBox() override = default;

  // Step
  inline void setStep(const T &value) { _step = value; }
  inline const T &step() const { return _step; }

  // StepFast
  inline void setStepFast(const T &value) { _stepFast = value; }
  inline const T &stepFast() const { return _stepFast; }

protected:
  virtual void paintElement() override { paintElementImpl(); }
  void paintElementImpl() {}
  void SpinBoxImpl() {}

  T _step{};
  T _stepFast{};
};

template <> inline void SpinBox<int>::SpinBoxImpl() {
  setTextFormat("%d");
  _step = 1;
  _stepFast = 10;
}

template <> inline void SpinBox<int>::paintElementImpl() {
  int value{_value};
  _changed = ImGui::InputInt(_label.c_str(), &value, _step, _stepFast);
  if (_changed) {
    setValue(value);
  }
}

template <> inline void SpinBox<float>::SpinBoxImpl() {
  setTextFormat("%.2f");
  _step = 0.1f;
  _stepFast = 1.0f;
}

template <> inline void SpinBox<float>::paintElementImpl() {
  float value{_value};
  _changed = ImGui::InputFloat(_label.c_str(), &value, _step, _stepFast,
                               _textFormat.c_str());
  if (_changed) {
    setValue(value);
  }
}

} // namespace Imw
