#pragma once
#include <ini.h>
#include <string>

namespace Imw {
class IElement {
public:
  virtual ~IElement() {}

  virtual int elementId() const = 0;
  virtual std::string elementIdStr() const = 0;
  virtual void paint() = 0;
  virtual bool handle() const = 0;
  virtual void trigger() const = 0;

  virtual void loadState(const mINI::INIStructure &ini) {}
  virtual void saveState(mINI::INIStructure &ini) {}

  virtual bool isValueElement() const { return false; }
  virtual bool isButtonElement() const { return false; }
};
} // namespace Imw
