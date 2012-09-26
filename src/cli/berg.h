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
#ifndef SRC_CLI_BERG_WRITER_H_
#define SRC_CLI_BERG_WRITER_H_

#include <iostream>
#include <fstream>

#include "src/berg_writer.h"

using std::ofstream;
using std::ifstream;
using std::fstream;
using std::istream;
using std::ios;

class Berg {
 public:
  static void Write(const char* file_name);
  static void WriteFile(istream& stream);

 private:
  Berg();
};
#endif  // SRC_CLI_BERG_WRITER_H_
