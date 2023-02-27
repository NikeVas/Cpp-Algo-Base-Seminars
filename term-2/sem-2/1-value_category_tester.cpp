#include "value_category_tester.hpp"

int main() {
  int x = 0;
  int&& y = 5;
  int&& rrx = std::move(x);

  int&& Foo();

  PRINT_VALUE_CATEGORY( x            );
  PRINT_VALUE_CATEGORY( std::move(x) );
  PRINT_VALUE_CATEGORY( y            );
  PRINT_VALUE_CATEGORY( rrx          );
  PRINT_VALUE_CATEGORY( Foo()        );
}
