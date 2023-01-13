#pragma once

namespace Imw {
class IElement {
public:
  virtual ~IElement() {}

  virtual void paint() = 0;
  virtual bool handle() = 0;
};
} // namespace Imw
