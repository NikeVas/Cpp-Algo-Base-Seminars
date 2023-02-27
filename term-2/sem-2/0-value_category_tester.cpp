#include "value_category_tester.hpp"

int main() {
  int x = 0;
  int& rx = x;
  const int& crx = x;
  const int& tmp = 11;

  int F();
  int& G();

  PRINT_VALUE_CATEGORY( x         );
  PRINT_VALUE_CATEGORY( rx        );
  PRINT_VALUE_CATEGORY( crx       );
  PRINT_VALUE_CATEGORY( tmp       );
  PRINT_VALUE_CATEGORY( 5         );

  PRINT_VALUE_CATEGORY( 2 + 2     );
  PRINT_VALUE_CATEGORY( x + crx   );
  PRINT_VALUE_CATEGORY( &x        );
  PRINT_VALUE_CATEGORY( &tmp      );
  PRINT_VALUE_CATEGORY( *(&x)     );
  PRINT_VALUE_CATEGORY( *(&crx)   );


  PRINT_VALUE_CATEGORY( x += 10   );
  PRINT_VALUE_CATEGORY( ++x       );
  PRINT_VALUE_CATEGORY( x++       );

  PRINT_VALUE_CATEGORY( F()       );
  PRINT_VALUE_CATEGORY( F() + F() );
  PRINT_VALUE_CATEGORY( G()       );
  PRINT_VALUE_CATEGORY( G() + G() );
  PRINT_VALUE_CATEGORY( G         );
  PRINT_VALUE_CATEGORY( &F        );

  PRINT_VALUE_CATEGORY( "lvalue"  );
}
