#pragma once

#define NODISCARD  [[nodiscard]]

#define BEGIN_GEOMETRY namespace geometry {
#define END_GEOMETRY  }

#define IN_NAEMSPACE_GEOMETRY(x) namespace geometry{ namespace x {
//#define END_NAMESPACE_GEOMETRY }
#define END_NAMESPACE_GEOMETRY(x) } }


#define ANONYM_NAMESPACE namespace{