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

#include "src/ice.h"

int main(int argc, char **argv) {
  // Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);

  // start the app
  if (strcmp("berg", argv[1]) == 0) {
    if (argc > 1) {
      Berg::Write(argv[2]);
    } else {
      Berg::WriteFile(std::cin);
    }
  } else if (strcmp("size", argv[1]) == 0) {
    Digest d;
    BergReader r(argv[2], d);
    cout << r.ChunkCount() << endl;
  } else if (strcmp("list", argv[1]) == 0) {
    Digest d;
    BergReader r(argv[2], d);
    ShaMap hashes = r.ListHashes();
    for (ShaMapper it = hashes->begin(); it != hashes->end(); ++it) {
      cout << Digest::ToString(it->first) << "\t" << it->second << endl;;
    }
  }
}
