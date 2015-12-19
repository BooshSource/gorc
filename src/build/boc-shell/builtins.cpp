#include "builtins.hpp"
#include "sexpr/sexpr.hpp"
#include "symbols.hpp"

using arglist = std::vector<gorc::sexpr>;

void gorc::register_builtins()
{
    register_builtin("atom", 1, [](arglist const &args)
            {
                return make_sexpr(atom(args.at(0)));
            });

    register_builtin("car", 1, [](arglist const &args)
            {
                return car(args.at(0));
            });

    register_builtin("cdr", 1, [](arglist const &args)
            {
                return cdr(args.at(0));
            });

    register_builtin("null", 1, [](arglist const &args)
            {
                return make_sexpr(null(args.at(0)));
            });
}
