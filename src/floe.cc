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
  ifstream file;
  file.open(file_name.c_str(), ios::in | ios::binary);
  assert(file.is_open());

  // skip magic
  file.seekg(sizeof(FLOE_MAGIC_HEADER), ios::beg);

  char *buffer = new char[sizeof(int64_t)];
  //TODO(gpetrovic): read the floe
}

void Floe::Write(string file_name) {
  Digest d;
  BergReader r(file_name, d);
  ShaMap hashes = r.ListHashes();
  Floe f;

  ofstream file;
  char* tmp_name = new char[11];
  GenRandom(tmp_name, 10);
  file.open(tmp_name, ios::out | ios::binary);
  assert(file.is_open());

  LOG(INFO) << "Write magic " << FLOE_MAGIC_HEADER;
  file.put(FLOE_MAGIC_HEADER);

  // leave room for chunk count
  file.seekp(sizeof(int64_t), ios::cur);

  vector<Location> locations;
  int64_t count = 0;
  size_t offset = sizeof(FLOE_MAGIC_HEADER);
  for (ShaMapper it = hashes->begin(); it != hashes->end(); ++it) {
    file.write((const char*)it->first.get(), SHA256_DIGEST_LENGTH);
    Location *loc = new Location(offset, it->second);
    locations.push_back(*loc);
    f.Put(it->first, loc);
    offset += loc->length + SHA256_DIGEST_LENGTH + CHUNK_LENGTH_BYTE_SIZE;
    ++count;
  }

  file.write((char*)&locations[0], sizeof(Location) * locations.size());
  file.seekp(1);
  file.write(reinterpret_cast<const char*>(&count), sizeof(count));

  file.close();
  string new_name = Digest::ToString(r.ReadHash());
  new_name.append(".floe");
  rename(tmp_name, new_name.c_str());
}
