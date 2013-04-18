#include <DO/Match.hpp>
#include <DO/Graphics.hpp>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

namespace DO {

  ostream & operator<<(ostream & os, const Match& m)
  {
    os << "source=" << m.sPos().transpose()
       << " target=" << m.tPos().transpose() << std::endl;
    os << "score=" << m.score() << " " << "rank=" << m.rank();
    return os;
  }

  bool writeMatches(const vector<Match>& matches, const std::string& fileName)
  {
    ofstream file(fileName.c_str());
    if (!file.is_open()) {
      std::cerr << "Cant open file" << fileName << std::endl;
      return false;
    }    

    file << matches.size() << std::endl;
    for(vector<Match>::const_iterator m = matches.begin(); m != matches.end(); ++m)
      file << m->sInd() << ' ' << m->tInd() << ' '
      << m->rank() << ' ' << m->score() << std::endl;

    return true;
  }

  bool readMatches(vector<Match>& matches, const std::string& fileName, float scoreT)
  {
    if (!matches.empty())
      matches.clear();

    std::ifstream file(fileName.c_str());
    if (!file.is_open()) {
      std::cerr << "Cant open file: " << fileName << std::endl;
      return false;
    }

    std::size_t matchCount;
    file >> matchCount;

    matches.reserve(matchCount);	
    for (size_t i = 0; i < matchCount; ++i)
    {
      Match m;

      file >> m.sInd() >> m.tInd() >> m.rank() >> m.score();
      if(m.score() > scoreT)
        break;

      matches.push_back(m);
    }

    return true;
  }

  bool readMatches(
    vector<Match>& matches, 
    const vector<Keypoint>& sKeys, const vector<Keypoint>& tKeys,
    const string& fileName, float scoreT)
  {
    if (!matches.empty())
      matches.clear();

    std::ifstream file(fileName.c_str());
    if (!file.is_open()) {
      std::cerr << "Cant open file: " << fileName << std::endl;
      return false;
    }

    std::size_t matchCount;
    file >> matchCount;

    matches.reserve(matchCount);	
    for (size_t i = 0; i < matchCount; ++i)
    {
      Match m;

      file >> m.sInd() >> m.tInd() >> m.rank() >> m.score();
      m.sPtr() = &sKeys[m.sInd()];
      m.tPtr() = &tKeys[m.tInd()];

      if(m.score() > scoreT)
        break;

      matches.push_back(m);
    }

    return true;
  }

  void drawImPair(const Image<Rgb8>& I1, const Image<Rgb8>& I2, const Point2f& off2, float scale)
  {
    display(I1, Point2f::Zero().cast<int>(), scale);
    display(I2, (off2*scale).cast<int>(), scale);
  }

  void drawMatch(const Match& m, const Color3ub& c, const Point2f& off2, float z)
  {
    m.sFeat().drawOnScreen(c, z);
    m.tFeat().drawOnScreen(c, z, off2);
    Point2f p1(m.sPos()*z);
    Point2f p2((m.tPos()+off2)*z);
    drawLine(p1, p2, c);
  }

  void drawMatches(const vector<Match>& matches, const Point2f& off2, float z)
  {
    for (vector<Match>::const_iterator m = matches.begin(); m != matches.end(); ++m)
      drawMatch(*m, Color3ub(rand()%256, rand()%256, rand()%256), off2, z);
  }

  void checkMatches(const Image<Rgb8>& I1, const Image<Rgb8>& I2, 
                    const vector<Match>& matches, bool redrawEverytime, float z)
  {
    Point2f off( float(I1.width()), 0.f );
    drawImPairH(I1, I2);
    for (vector<Match>::const_iterator m = matches.begin(); m != matches.end(); ++m)
    {
      if (redrawEverytime)
        drawImPairH(I1, I2, z);
      drawMatch(*m, Color3ub(rand()%256, rand()%256, rand()%256), off, z);
      cout << *m << endl;
      getKey();
    }
  }

} /* namespace DO */