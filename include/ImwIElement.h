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
  virtual bool handle() = 0;
  virtual void trigger() = 0;

  virtual void loadState(const mINI::INIStructure &ini) {}
  virtual void saveState(mINI::INIStructure &ini) {}
};
} // namespace Imw
