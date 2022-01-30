template <typename Elem>
class Foo {

  // Must be virtual as we'll inherit from Foo.
  virtual ~Foo();

  virtual int GetSize() const noexcept = 0;
  virtual void Push(const Elem& x) = 0;
};
