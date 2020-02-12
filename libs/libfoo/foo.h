class IBar;

class Foo
{
public:
    explicit Foo(IBar& bar);
    bool baz(bool useQux);
protected:
    IBar& m_bar;
};
