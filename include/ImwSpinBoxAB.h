#pragma once
#include "ImwValueElement.h"
#include <algorithm>
#include <array>

namespace Imw {
template <class T> class SpinBoxAB : public ValueElement<std::array<T, 2>> {
public:
  SpinBoxAB(const std::string &label = {})
      : ValueElement<std::array<T, 2>>(label) {}

  virtual ~SpinBoxAB() override {}

  inline void setValueLimitsA(const std::pair<T, T> &limits) {
    ValueElement<std::array<T, 2>>::_valueLimits.first[0] = limits.first;
    ValueElement<std::array<T, 2>>::_valueLimits.second[0] = limits.second;
  }

  inline void setValueLimitsB(const std::pair<T, T> &limits) {
    ValueElement<std::array<T, 2>>::_valueLimits.first[1] = limits.first;
    ValueElement<std::array<T, 2>>::_valueLimits.second[1] = limits.second;
  }

protected:
  virtual void paintElement() override {
    paintElementImpl();

    ValueElement<std::array<T, 2>>::_value[0] =
        std::clamp<T>(ValueElement<std::array<T, 2>>::_value[0],
                      ValueElement<std::array<T, 2>>::_valueLimits.first[0],
                      ValueElement<std::array<T, 2>>::_valueLimits.second[0]);

    ValueElement<std::array<T, 2>>::_value[1] =
        std::clamp<T>(ValueElement<std::array<T, 2>>::_value[1],
                      ValueElement<std::array<T, 2>>::_valueLimits.first[1],
                      ValueElement<std::array<T, 2>>::_valueLimits.second[1]);
  }
  void paintElementImpl() {}
};

template <> inline void SpinBoxAB<int>::paintElementImpl() {
  int step{1};
  int step_fast{100};
  ImGuiInputTextFlags flags{0};
  ImGui::InputScalarN(_label.c_str(), ImGuiDataType_S32, (void *)_value.data(),
                      2, (void *)(step > 0 ? &step : NULL),
                      (void *)(step_fast > 0 ? &step_fast : NULL), NULL, flags);
}
} // namespace Imw
