/// Copyright 2012, (c) Daniel Fanjul Alcuten, Goran Petrovic

/// This file is part of ice.
/// ice is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// ice is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with ice.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SRC_FLOE_H_
#define SRC_FLOE_H_

#include <map>
#include <list>
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "src/magic.h"
#include "src/berg_reader.h"

using std::map;
using std::list;
using std::ofstream;
using std::vector;
using boost::shared_ptr;

typedef struct _Location {
  int offset;
  int length;

  _Location(int off, int len) : offset(off), length(len) {
  }
} Location;

typedef shared_ptr<const Location> LocationView;

class Floe {
 public:
  explicit Floe();
  explicit Floe(Sha sha);

  Sha sha();
  void set_sha(Sha sha);

  int Size();
  LocationView Get(Sha sha);
  void Put(Sha sha, int offset, int length);
  void Put(Sha sha, Location* location);
  map<Sha, LocationView> List();

  static Floe Read(string file_name);
  void Write(string file_name);

 private:
  Sha sha_;
  map<Sha, LocationView> locations_;
};

#endif  // SRC_FLOE_H_
