#pragma once
#include "ImwMultiValueElement.h"
#include <algorithm>
#include <array>

namespace Imw {
template <typename T> class MultiSpinBox : public MultiValueElement<T> {
  using Base = MultiValueElement<T>;

public:
  // Constructor
  MultiSpinBox(std::size_t count, const std::string &label = {})
      : Base(count, label) {
    _valueStep.resize(count);
    _valueFastStep.resize(count);
    _valueLimits.resize(count);
    MultiSpinBoxImpl();
  }

  // Destructor
  virtual ~MultiSpinBox() override = default;

  // Set Value
  virtual void setValue(const T &value, std::size_t index) override {
    Base::setValue(std::clamp(value, _valueLimits.at(index).first,
                              _valueLimits.at(index).second),
                   index);
  }

  // Set Value Step
  virtual void setValueStep(const T &step, std::size_t index) override {
    _valueStep.at(index) = step;
  }

  // Set Value Fast Step
  virtual void setValueFastStep(const T &fstep, std::size_t index) override {
    _valueFastStep.at(index) = fstep;
  }

protected:
  virtual void paintElement() override { paintElementImpl(); }
  inline void paintElementImpl() {}
  void MultiSpinBoxImpl() {}

  std::vector<T> _valueStep{};
  std::vector<T> _valueFastStep{};
  std::vector<std::pair<T, T>> _valueLimits{};
};

// MultiSpinBox<int>
// -----------------------------------------------------------------------------

template <> inline void MultiSpinBox<int>::MultiSpinBoxImpl() {
  _textFormat = "%d";
  std::fill(_valueStep.begin(), _valueStep.end(), 1);
  std::fill(_valueFastStep.begin(), _valueFastStep.end(), 10);
}

template <> inline void MultiSpinBox<int>::paintElementImpl() {
  ImGuiInputTextFlags flags{0};
  ImGui::InputScalarN(_label.c_str(), ImGuiDataType_S32,
                      Base::_valueList.data(), Base::_valueList.size(),
                      _valueStep.data(), _valueFastStep.data(),
                      _textFormat.c_str(), flags);
}

// MultiSpinBox<float>
// -----------------------------------------------------------------------------

template <> inline void MultiSpinBox<float>::MultiSpinBoxImpl() {
  _textFormat = "%.2f";
  std::fill(_valueStep.begin(), _valueStep.end(), 0.1f);
  std::fill(_valueFastStep.begin(), _valueFastStep.end(), 1.0f);
}

template <> inline void MultiSpinBox<float>::paintElementImpl() {
  ImGuiInputTextFlags flags{0};
  ImGui::InputScalarN(_label.c_str(), ImGuiDataType_Float,
                      Base::_valueList.data(), Base::_valueList.size(),
                      _valueStep.data(), _valueFastStep.data(),
                      _textFormat.c_str(), flags);
}

} // namespace Imw
