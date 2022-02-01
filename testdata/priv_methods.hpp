#include <utility>

struct Gadget {};

class Foo {
 public:

    virtual bool Transform(Gadget* g, std::pair<int, bool> p) noexcept = 0;

 protected:
  virtual std::pair<int, bool> Resume();

 private:
  virtual int GetTimeOut() const;
};
