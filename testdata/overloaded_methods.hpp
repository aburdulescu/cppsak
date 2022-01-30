struct Element {};
struct Bar {};

class Foo {

  // Must be virtual as we'll inherit from Foo.
  virtual ~Foo();

  // Overloaded on the types and/or numbers of arguments.
  virtual int Add(Element x);
  virtual int Add(int times, Element x);

  // Overloaded on the const-ness of this object.
  virtual Bar& GetBar() noexcept;
  virtual const Bar& GetBar() const noexcept;
};
