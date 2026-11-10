#include "Notation.hpp"
#include <stdexcept>
#include <string>

namespace Notation {

Move parseMove(std::string_view token) {
  if (token.empty() || token.size() > 2) {
    throw std::invalid_argument("Invalid move token: \"" + std::string(token) + "\"");
  }

  const char face = token[0];

  if (token.size() == 1) {
    switch (face) {
      case 'U': return Move::U;
      case 'D': return Move::D;
      case 'F': return Move::F;
      case 'B': return Move::B;
      case 'L': return Move::L;
      case 'R': return Move::R;
      default: break;
    }
  } else if (token.size() == 2) {
    const char modifier = token[1];
    if (modifier == '\'') {
      switch (face) {
        case 'U': return Move::U_PRIME;
        case 'D': return Move::D_PRIME;
        case 'F': return Move::F_PRIME;
        case 'B': return Move::B_PRIME;
        case 'L': return Move::L_PRIME;
        case 'R': return Move::R_PRIME;
        default: break;
      }
    } else if (modifier == '2') {
      switch (face) {
        case 'U': return Move::U2;
        case 'D': return Move::D2;
        case 'F': return Move::F2;
        case 'B': return Move::B2;
        case 'L': return Move::L2;
        case 'R': return Move::R2;
        default: break;
      }
    }
  }

  throw std::invalid_argument("Unrecognized WCA move token: \"" + std::string(token) + "\"");
}

std::string_view moveToString(Move move) noexcept {
  switch (move) {
    case Move::U:       return "U";
    case Move::U_PRIME: return "U'";
    case Move::U2:      return "U2";

    case Move::D:       return "D";
    case Move::D_PRIME: return "D'";
    case Move::D2:      return "D2";

    case Move::F:       return "F";
    case Move::F_PRIME: return "F'";
    case Move::F2:      return "F2";

    case Move::B:       return "B";
    case Move::B_PRIME: return "B'";
    case Move::B2:      return "B2";

    case Move::L:       return "L";
    case Move::L_PRIME: return "L'";
    case Move::L2:      return "L2";

    case Move::R:       return "R";
    case Move::R_PRIME: return "R'";
    case Move::R2:      return "R2";
  }
  return "";
}

} // namespace Notation

