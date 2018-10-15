#pragma once

#include <algorithm> // max
#include <map>
#include <utility> // pair
#include <tuple> // make_tuple, get
#include <type_traits> // integral_constant
#include <vector>

#define EASYDUMP__VERSION_MAJOR 0
#define EASYDUMP__VERSION_MINOR 0
#define EASYDUMP__VERSION_PATCH 0

namespace easydump {
  static constexpr struct {
    uint8_t major, minor, patch;
  } version = {
    EASYDUMP__VERSION_MAJOR,
    EASYDUMP__VERSION_MINOR,
    EASYDUMP__VERSION_PATCH
  };
}

namespace easydump {
namespace txt{

  // internal implementations
  template<typename T, typename O>
  inline void _dump(const T &x, O &out) {
    out << x;
  }

  template<typename T, typename I>
  inline void _load(T &x, I &in) {
    in >> x;
  }


  // interfaces
  template<typename T, typename IO>
  inline void dump(const T &x, IO &io);

  template<typename T, typename IO>
  inline void load(T &x, IO &io);

  template<typename T>
  struct depth;

  constexpr auto delims = std::make_tuple("", " ", "\n", "\n\n", "\n\n\n");
  template<typename T>
  struct get_delim {
    using data_type = std::remove_cv_t<std::remove_reference_t<T>>;
    static constexpr auto value = std::get<depth<data_type>::value>(delims);
  };


  // int
  template<typename IO>
  inline void dump(const int &x, IO &io) {
    _dump(x, io);
  }

  template<typename IO>
  inline void load(int &x, IO &io) {
    _load(x, io);
  }

  template<>
  struct depth<int> : std::integral_constant<unsigned, 0> {} ;

  template<>
  struct depth<const int> : std::integral_constant<unsigned, 0> {} ;


  // double
  template<typename IO>
  inline void dump(const double &x, IO &io) {
    _dump(x, io);
  }

  template<typename IO>
  inline void load(double &x, IO &io) {
    _load(x, io);
  }

  template<>
  struct depth<double> : std::integral_constant<unsigned, 0> {} ;

  template<>
  struct depth<const double> : std::integral_constant<unsigned, 0> {} ;


  // std::pair
  template<typename T1, typename T2, typename IO>
  inline void dump(const std::pair<T1, T2> &p, IO &io) {
    constexpr auto delim = get_delim<decltype(p)>::value;
    dump(p.first, io); _dump(delim, io); dump(p.second, io);
  }

  template<typename T1, typename T2, typename IO>
  inline void load(std::pair<T1, T2> &p, IO &io) {
    load(p.first, io); load(p.second, io);
  }

  template<typename T1, typename T2>
  struct depth<std::pair<T1, T2>> : std::integral_constant<unsigned,
    1 + std::max(depth<T1>::value, depth<T2>::value)> {} ;


  // std::vector
  template<typename elem_type, typename IO>
  inline void dump(const std::vector<elem_type> &v, IO &io) {
    constexpr auto delim = get_delim<decltype(v)>::value;
    _dump(v.size(), io);
    for ( const elem_type &elem : v) {_dump(delim, io); dump(elem, io); }
  }

  template<typename elem_type, typename IO>
  inline void load(std::vector<elem_type> &v, IO &io) {
    decltype(v.size()) n; _load(n, io);
    v.resize(n);
    for ( elem_type &elem : v) _load(elem, io);
  }

  template<typename elem_type>
  struct depth<std::vector<elem_type>> : std::integral_constant<unsigned,
    1 + depth<elem_type>::value> {} ;

  // std::map
  template<typename key_type, typename value_type, typename IO>
  inline void dump(const std::map<key_type, value_type> &m, IO &io) {
    constexpr auto delim = get_delim<decltype(m)>::value;
    _dump(m.size(), io);
    for ( const auto &kv : m) {
      _dump(delim, io);
      constexpr auto delim_kv = get_delim<decltype(kv)>::value;
      dump(kv.first, io); _dump(delim_kv, io); dump(kv.second, io);
    }
  }

  template<typename key_type, typename value_type, typename IO>
  inline void load(std::map<key_type, value_type> &m, IO &io) {
    decltype(m.size()) n; _load(n, io);
    m.clear();
    for ( decltype(n) i = 0; i < n; i++ ) {
      std::pair<key_type, value_type> p;
      load(p.first, io); load(p.second, io);
      m[p.first] = p.second;
    }
  }

  template<typename key_type, typename value_type>
  struct depth<std::map<key_type, value_type>> : std::integral_constant<unsigned,
    1 + depth<std::pair<key_type, value_type>>::value> {} ;
}
}


namespace easydump {
namespace bin {

  // internal implementations
  template<typename T, typename O>
  inline void _dump(const T &x, O &out) {
    out.write(reinterpret_cast<const char*>(&x), sizeof(T));
  }

  template<typename T, typename I>
  inline void _load(T &x, I &in) {
    in.read(reinterpret_cast<char*>(&x), sizeof(T));
  }


  // interfaces
  template<typename T, typename IO>
  inline void dump(const T &x, IO &io);

  template<typename T, typename IO>
  inline void load(T &x, IO &io);


  // int
  template<typename IO>
  inline void dump(const int &x, IO &io) {
    _dump(x, io);
  }

  template<typename IO>
  inline void load(int &x, IO &io) {
    _load(x, io);
  }


  // double
  template<typename IO>
  inline void dump(const double &x, IO &io) {
    _dump(x, io);
  }

  template<typename IO>
  inline void load(double &x, IO &io) {
    _load(x, io);
  }


  // std::pair
  template<typename T1, typename T2, typename IO>
  inline void dump(const std::pair<T1, T2> &p, IO &io) {
    dump(p.first, io); dump(p.second, io);
  }

  template<typename T1, typename T2, typename IO>
  inline void load(std::pair<T1, T2> &p, IO &io) {
    load(p.first, io); load(p.second, io);
  }


  // std::vector
  template<typename elem_type, typename IO>
  inline void dump(const std::vector<elem_type> &v, IO &io) {
    int n = v.size(); _dump(n, io);
    for ( const elem_type &elem : v) dump(elem, io);
  }

  template<typename elem_type, typename IO>
  inline void load(std::vector<elem_type> &v, IO &io) {
    int n; _load(n, io);
    v.resize(n);
    for ( elem_type &elem : v) _load(elem, io);
  }


  // std::map
  template<typename key_type, typename value_type, typename IO>
  inline void dump(const std::map<key_type, value_type> &m, IO &io) {
    int n = m.size(); _dump(n, io);
    for ( const auto &kv : m) {
      dump(kv.first, io); dump(kv.second, io);
    }
  }

  template<typename key_type, typename value_type, typename IO>
  inline void load(std::map<key_type, value_type> &m, IO &io) {
    int n; _load(n, io);
    m.clear();
    for ( decltype(n) i = 0; i < n; i++ ) {
      std::pair<key_type, value_type> p;
      load(p.first, io); load(p.second, io);
      m[p.first] = p.second;
    }
  }
}
}
