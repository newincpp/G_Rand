#ifndef TEMPLATEHELPER_H_
# define TEMPLATEHELPER_H_

namespace GRand {
    template <typename, bool>
    struct DeclareIf { };
    template <typename T>
    struct DeclareIf<T, true> { T value; };
}

#endif /* !TEMPLATEHELPER_H_ */
