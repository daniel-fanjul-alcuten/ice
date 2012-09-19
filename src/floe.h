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

#include "src/digest.h"
#include "src/chunk.h"

using std::map;
using std::list;

typedef struct {
  int offset;
  int length;
} Location;

class Floe {
 public:
  explicit Floe();
  explicit Floe(Sha sha);

  Sha sha();
  void set_sha(Sha sha);

  int size();
  Location get(Sha sha);
  void put(Sha sha, int offset, int length);
  void put(Sha sha, Location location);
  map<Sha, Location>::const_iterator list();

  static Floe read(FILE* file);
  void write(FILE* file);

 private:
  Sha sha_;
  map<Sha, Location> locations_;
};

#endif  // SRC_FLOE_H_
