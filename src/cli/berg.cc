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

#include "src/cli/berg.h"

void Berg::Write(const char* file_name) {
  ifstream stream(file_name, ios::in | ios::binary);
  Berg::WriteFile(stream);
  stream.close();
}

void Berg::WriteFile(istream& stream) {
  Digest d;
  char* tmp_name = new char[11];
  GenRandom(tmp_name, 10);
  BergWriter w(tmp_name, d);
  char *buffer = new char[MAX_CHUNK_SIZE];

  stream.read(buffer, MAX_CHUNK_SIZE);
  ChunkData data(buffer, stream.gcount());
  Chunk c(data);
  w.WriteChunk(c);

  while (!stream.eof()) {
    stream.read(buffer, MAX_CHUNK_SIZE);
    data.length = stream.gcount();
    c.Create(data);
    w.WriteChunk(c);
  }

  string new_name = Digest::ToString(w.Close());
  new_name.append(".berg");
  std::cout << new_name << std::endl;
  rename(tmp_name, new_name.c_str());
}
