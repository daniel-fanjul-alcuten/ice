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

#include "src/floe.h"

Floe::Floe() {
}

Floe::Floe(Sha sha) : sha_(sha) {
}

Sha Floe::sha() {
  return sha_;
}

void Floe::set_sha(Sha sha) {
  sha_ = sha;
}

int Floe::size() {
  return locations_.size();
}

Location Floe::get(Sha sha) {
  map<Sha, Location>::iterator it = locations_.find(sha);
  if (it != locations_.end()) {
    return it->second;
  }
  Location location = {0, 0};
  return location;
}

void Floe::put(Sha sha, int offset, int length) {
  Location location = {offset, length};
  locations_[sha] = location;
}

void Floe::put(Sha sha, Location location) {
  locations_[sha] = location;
}

map<Sha, Location>::const_iterator Floe::list() {
  return locations_.begin();
}

Floe Floe::read(FILE* file) {
  // TODO(dfanjul): Floe::read()
}

void Floe::write(FILE* file) {
  // TODO(dfanjul): Floe::write()
}
