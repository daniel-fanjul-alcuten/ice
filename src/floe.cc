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

int Floe::Size() {
  return locations_.size();
}

LocationView Floe::Get(Sha sha) {
  map<Sha, LocationView>::iterator it = locations_.find(sha);
  if (it != locations_.end()) {
    return it->second;
  }
  return LocationView();
}

void Floe::Put(Sha sha, int offset, int length) {
  locations_[sha] = LocationView(new Location(offset, length));
}

void Floe::Put(Sha sha, Location* location) {
  locations_[sha].reset(location);
}

map<Sha, LocationView> Floe::List() {
  return locations_;
}

Floe Floe::Read(string file_name) {
  // TODO(dfanjul): Floe::read()
}

void Floe::Write(string file_name) {
  // TODO(dfanjul): Floe::write()
}
