/******************************************************************************
 * Filename: bal.c        Description: balanced parens & brackets in logspace
 * Author: Owen Reiss     Assignment: Math 387, Homework 8, Bonus 4
 *
 * While the following algorithm runs in O(log n) space, it does so only at
 * the considerable expense of requiring O(n^2) time. To achieve this tradeoff,
 * the algorithm reads through the input multiple times -- once for each level
 * of parenthesis nesting (e.g., the string "((([])))" is read four times).
 * On each pass, it is made sure that the brackets in that parenthesis level,
 * and only at that level (neither lower nor higher levels), are properly
 * nested. At the end, if every level is balanced, the algorithm accepts. This
 * explanation glosses over two (minor) things: first, the nesting of
 * parentheses is verified at the same time as the nesting of brackets; and
 * second, there is one more pass, at the beginning, to count the number of
 * levels of parentheses. Finally, unless you are very tight for space, this
 * algorithm should really be kept away from since the runtime is not so good.
 ******************************************************************************/

#include <stdio.h>

#define fail(msg) { \
  fprintf(stderr, "bal: %s at %ld\n", msg, s - t); \
  return 0; \
}

int bal(char *s) {
  int n = 0;    /* num levels of parens */
  int p, r;     /* current paren/bracket depth */
  char *t = s;  /* save string pointer */

  /* count levels of parens */
  while (*s) switch (*s++) {
    case '(': n++;
  }

  /* check if balanced at each level */
  for (int i = 0; p = 0, r = 0, s = t, i <= n; i++) {
    while (*s) switch (*s++) {
      case '(':
        p++;
        break;
      case ')':
        if (p == i)
          if (r > 0) fail("expected bracket");
        p == 0 ? (fail("unmatched paren")) : p--;
        break;
      case '[':
        if (p == i)
          r++;
        break;
      case ']':
        if (p == i)
          r == 0 ? (fail("unmatched bracket")) : r--;
        break;
      default:
        fail("unknown character");
    }
    
    if (p > 0) fail("expected paren");
    if (r > 0) fail("expected bracket");
  }

  return 1;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("bal: missing input string\n");
    return 1;
  }

  return bal(argv[1]) ? 0 : 1;
}
