#include "tuple.hpp"
#include <iostream>

using namespace std;

class Json {
public:
  using IdType = const char*;
};

class Energy {};


/************************ static command methods *********************/


template <typename Doc> class CommandBase {
public:
  static Doc deserialize(const char*);
  static bool matches(const Doc& d, typename Doc::IdType id);
  static Doc makeErrorResponse(const char* err);
};

template <> Json CommandBase<Json>::deserialize(const char*) { return Json(); }
template <> bool CommandBase<Json>::matches(const Json& d, const char* id) {
  return true;
}
template <> Json CommandBase<Json>::makeErrorResponse(const char* err) {
  return Json();
}

/************************ Generic command *********************/

template <typename Doc, typename Concrete>
class Command : public CommandBase<Doc> {
private:
  using Id = typename Doc::IdType;
  Id mId;
  Concrete& mConcrete;

protected:
  char err[120] = {0};

public:
  Command(const Id id, Concrete& concrete) : mId(id), mConcrete(concrete) {}
  bool parse(const Doc& d) { return mConcrete.parse(d); }
  const Doc run(const Doc& d) {
    if (parse(d))
    {
      return mConcrete.run();
    } else
    {
      return CommandBase<Doc>::makeErrorResponse(err);
    }
  }
};

/***************** Specific command *********************/


class Command_SET_INFO_MEASURE_Base {
public:
protected:
  bool validate(int, float) { return true; }
  bool execute (int, float) { return true; }
};

template <typename Doc>
class Command_SET_INFO_MEASURE
    : public Command<Doc, Command_SET_INFO_MEASURE<Doc>>,
      public Command_SET_INFO_MEASURE_Base {

private:
  const Energy& mEnergy;
  bool m_sample_on;

public:
  Command_SET_INFO_MEASURE(typename Doc::IdType id, const Energy& energy)
      : mEnergy(energy), m_sample_on(false),
        Command<Doc, Command_SET_INFO_MEASURE>(id, *this) {}
  bool parse(const Doc& d);
  // Do not hide base class run method
  using Command<Doc, Command_SET_INFO_MEASURE<Doc>>::run;
  Doc run();
};


/****************************  Parsing *******************************/

/*----- Generic parser --------*/
template <typename Doc, typename Schema> class CommandParser {
public:
  bool parse(const Doc&);
};

/*----- Json parser --------*/
template <typename Schema> class CommandParser<Json, Schema> {
public:
  bool parse(const Json&, const char* errOut) { return true; }
};


/*----- Generic schema --------*/
template <typename Cmd> class Schema {};


/*----- Specific command schema -------*/
template <> class Schema<Command_SET_INFO_MEASURE_Base> {
  static constexpr const int x = 0;
};

/*----- Specific command json schema -------*/
template <>
class Schema<Command_SET_INFO_MEASURE<Json>>
    : public Schema<Command_SET_INFO_MEASURE_Base> {};


/***************** Specific Command Json Impl *********************/

template <> bool Command_SET_INFO_MEASURE<Json>::parse(const Json& d) {

  // Json generic parsing
  CommandParser<Json, Schema<Command_SET_INFO_MEASURE<Json>>> cp;
  // m_sample_on = true; // Lo sacamos del json d.
  err[1] = 'a';
  return true;
}
template <> Json Command_SET_INFO_MEASURE<Json>::run() {
  execute(1, 2.0);
  return makeErrorResponse("error");
}

/***************** MAIN *********************/



//int main() {
//  const char* id = "id";
//  Command_SET_INFO_MEASURE<Json> c(id, Energy());
//  c.run(Json());


//}
