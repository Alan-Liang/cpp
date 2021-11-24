// 你无需修改、提交以下代码，即，你最终的提交 **不应该** 包含以下代码。
// 本题评测时使用的 object 类存放于名为 base.hpp 的文件里，你最终的提交需要 include 该头文件以避免 ce 。
// 即，你的提交应包含一行 #include "base.hpp" 。

// 以下函数说明只是便于理解，详细的要求见各个派生类的说明。
#include <iostream>

#include <string>
using namespace std;
class object {
 protected:
  string contain;
 public:
  // 构造函数。
  object() = default;
  object(string _contain_) : contain(_contain_) {}

  // copy 函数，将 o 指针对应的类的信息拷贝到调用该函数的类对象上。
  // 保证 o 与 this 是同一种派生类指针，但会以 object * 的形式传入。
  // 具体可以参考 main 函数中的调用方式。
  virtual void copy(object* o) = 0;

  // 参数为某个日期，返回一个字符串，代表此日期快递的派送状态。
  virtual string send_status(int y, int m, int d) = 0;

  // 返回派送快递的方法。详见各个派生类的说明。
  virtual string type() = 0;

  // 输出保存于类内的信息，具体格式详见各个派生类的说明。
  virtual void print() {
    cout << "[object] contain: " << contain << endl;
    // 注意：本题评测时使用的 object 类会与这里的版本有微小的区别，但不会对于完成本题有影响。
  }

  // 析构函数。
  virtual ~object() {}
};






#ifdef ONLINE_JUDGE
#include "base.hpp"
#endif

#include <algorithm>
#include <string>

struct date {
  int year, month, day;
  date() = default;
  date(int y, int m, int d) : year(y), month(m), day(d) {}
  //todo 实现流输入
  //todo 实现 operator< 的重载
};


std::istream& operator>> (std::istream &is, date &ts) {
  is >> ts.year >> ts.month >> ts.day;
  return is;
}
bool operator< (const date &lhs, const date &rhs) {
  if (lhs.year != rhs.year) return lhs.year < rhs.year;
  if (lhs.month != rhs.month) return lhs.month < rhs.month;
  if (lhs.day != rhs.day) return lhs.day < rhs.day;
  return false;
}
bool operator== (const date &lhs, const date &rhs) {
  if (lhs.year != rhs.year) return false;
  if (lhs.month != rhs.month) return false;
  if (lhs.day != rhs.day) return false;
  return true;
}

class mail : public object {
 protected:
  std::string postmark;
  date send_date;
  date arrive_date;
 public:
  mail () {}
  mail(std::string contain, std::string postmark, date send_date, date arrive_date) : object(contain), postmark(postmark), send_date(send_date), arrive_date(arrive_date) {}
  ~mail () {}
  void copy (object *o) {
    mail &m = *dynamic_cast<mail *>(o);
    contain = m.contain;
    postmark = m.postmark;
    send_date = m.send_date;
    arrive_date = m.arrive_date;
  }
  std::string send_status (int y, int m, int d) {
    return "not send";
  }
  std::string type () {
    return "no type";
  }
  void print () {
    object::print();
    std::cout << "[mail] postmark: " << postmark << std::endl;
  }
};
class air_mail : public mail {
 protected:
  std::string airline;
  date take_off_date;
  date land_date;
 public:
  air_mail () {}
  air_mail (
    std::string contain,
    std::string postmark,
    date send_date,
    date arrive_date,
    date take_off_date,
    date land_date,
    std::string airline
  ) : mail(contain, postmark, send_date, arrive_date), take_off_date(take_off_date), land_date(land_date), airline(airline) {}
  ~air_mail () {}
  void copy (object *o) {
    air_mail &m = *dynamic_cast<air_mail *>(o);
    contain = m.contain;
    postmark = m.postmark;
    send_date = m.send_date;
    arrive_date = m.arrive_date;
    take_off_date = m.take_off_date;
    land_date = m.land_date;
    airline = m.airline;
  }
  std::string send_status (int y, int m, int d) {
    date ask_date(y, m, d);
    if (ask_date < send_date)
      return "mail not send";
    else if (ask_date < take_off_date)
      return "wait in airport";
    else if (ask_date < land_date)
      return "in flight";
    else if (ask_date < arrive_date)
      return "already land";
    else
      return "already arrive";
  }
  std::string type () { return "air"; }
  void print () {
    mail::print();
    std::cout << "[air] airlines: " << airline << std::endl;
  }
};
class train_mail : public mail {
 protected:
  int station_num = 0;
  std::string *station_name = nullptr;
  date *station_time = nullptr;
 public:
  train_mail () {}
  train_mail (
    std::string contain,
    std::string postmark,
    date send_date,
    date arrive_date,
    std::string *station_name_,
    date *station_time_,
    int station_num
  ) : mail(contain, postmark, send_date, arrive_date), station_num(station_num) {
    station_name = new std::string[station_num];
    station_time = new date[station_num];
    for (int i = 0; i < station_num; ++i) {
      station_time[i] = station_time_[i];
      station_name[i] = station_name_[i];
    }
  }
  ~train_mail () {
    delete[] station_name;
    delete[] station_time;
  }
  void copy (object *o) {
    train_mail &m = *dynamic_cast<train_mail *>(o);
    if (dynamic_cast<train_mail *>(o) == this) return;
    contain = m.contain;
    postmark = m.postmark;
    send_date = m.send_date;
    arrive_date = m.arrive_date;
    delete[] station_time;
    delete[] station_name;
    station_num = m.station_num;
    station_name = new std::string[station_num];
    station_time = new date[station_num];
    for (int i = 0; i < station_num; ++i) {
      station_time[i] = m.station_time[i];
      station_name[i] = m.station_name[i];
    }
  }
  std::string send_status (int y, int m, int d) {
    date query_date (y, m, d);
    if (query_date < send_date) return "mail not send";
    if (!(query_date < arrive_date)) return "already arrive";
    date *x = std::lower_bound(station_time, station_time + station_num, query_date);
    int offset = x - station_time;
    if (query_date == station_time[offset]) return "at " + station_name[offset];
    if (offset == 0) return "wait in departure station";
    if (offset == station_num) return "wait in terminus station";
    return "between " + station_name[offset - 1] + " and " + station_name[offset];
    if (query_date < station_time[0]) return "wait in departure station";
    for (int i = 0; i < station_num; ++i) if (query_date == station_time[i]) return std::string("at ") + station_name[i];
    for (int i = 0; i < station_num - 1; ++i) if (
      station_time[i] < query_date &&
      query_date < station_time[i + 1]
    ) return std::string("between ") + station_name[i] + std::string(" and ") + station_name[i + 1];
    if (station_time[station_num - 1] < query_date && query_date < arrive_date) return "wait in terminus station";
    return "already arrive";
  }
  // std::string send_status (int y, int m, int d) {
  //   date query_date {y, m, d};
  //   if (query_date < send_date) return "mail not arrived";
  //   if (!(query_date < arrive_date)) return "already arrive";
  //   date *item = std::lower_bound(station_time, station_time + station_num, query_date);
  //   int station_num_arriving = item - station_time;
  //   if (query_date == station_time[station_num_arriving]) return "at " + station_name[station_num_arriving];
  //   if (station_num_arriving == 0) return "wait in departure station";
  //   if (station_num_arriving == station_num) return "wait in terminus station";
  //   return "between " + station_name[station_num_arriving - 1] + " and " + station_name[station_num_arriving];
  // }
  std::string type () {
    return "train";
  }
  void print () {
    mail::print();
    std::cout << "[train] station_num: " << station_num << std::endl;
  }
};
class car_mail : public mail {
 protected:
  int mile;
  std::string driver_name;
  static int timeDelta (const date &lhs, const date &rhs) {
    return (rhs.year - lhs.year) * 360 + (rhs.month - lhs.month) * 30 + rhs.day - lhs.day;
  }
  double getMile (const date &ts) {
    int used = timeDelta(send_date, ts);
    int total = timeDelta(send_date, arrive_date);
    return static_cast<double>(used) / static_cast<double>(total) * static_cast<double>(mile);
  }
 public:
  car_mail () {}
  car_mail (
    string contain,
    string postmark,
    date send_date,
    date arrive_date,
    int mile,
    std::string driver_name
  ) : mail(contain, postmark, send_date, arrive_date), mile(mile), driver_name(driver_name) {}
  ~car_mail () {}
  void copy (object *o) {
    car_mail &m = *dynamic_cast<car_mail *>(o);
    contain = m.contain;
    postmark = m.postmark;
    send_date = m.send_date;
    arrive_date = m.arrive_date;
    mile = m.mile;
    driver_name = m.driver_name;
  }
  std::string send_status (int y, int m, int d) {
    date query_date (y, m, d);
    if (query_date < send_date) return "mail not send";
    if (query_date < arrive_date) return std::string("at ") + std::to_string(getMile(query_date));
    return "already arrive";
  }
  std::string type () {
    return "car";
  }
  void print () {
    mail::print();
    std::cout << "[car] driver_name: " << driver_name << std::endl;
  }
};

template <typename TL, typename TR>
void __swap_impl (object *lhs, object *rhs) {
  TL tmp;
  tmp.copy(lhs);
  dynamic_cast<TR *>(lhs)->copy(rhs);
  dynamic_cast<TL *>(rhs)->copy(&tmp);
}

template <typename T>
void _swap_impl (object *lhs, object *rhs) {
  std::string tR = rhs->type();
  if (tR == "no type") __swap_impl<T, mail>(lhs, rhs);
  if (tR == "air") __swap_impl<T, air_mail>(lhs, rhs);
  if (tR == "train") __swap_impl<T, train_mail>(lhs, rhs);
  if (tR == "car") __swap_impl<T, car_mail>(lhs, rhs);
}

//void obj_swap (object *lhs, object *rhs) {
//  std::string tL = lhs->type();
//  if (tL == "no type") _swap_impl<mail>(lhs, rhs);
//  if (tL == "air") _swap_impl<air_mail>(lhs, rhs);
//  if (tL == "train") _swap_impl<train_mail>(lhs, rhs);
//  if (tL == "car") _swap_impl<car_mail>(lhs, rhs);
//}

void obj_swap (object *&lhs, object *&rhs) {
  object *tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}





#include <iostream>
#include <algorithm>
#ifdef ONLINE_JUDGE
#include "src.hpp" // 你提交的代码
#endif
using namespace std;

void obj_copy(object* ori,object*& cop){
  string type=ori->type();
  if(type=="no type")
    cop=new mail();
  else if(type=="air")
    cop=new air_mail();
  else if(type=="train")
    cop=new train_mail();
  else if(type=="car")
    cop=new car_mail();
  cop->copy(ori);
}

const int readinSize=100000;
int main(){
  ios::sync_with_stdio(false);
  int mailNum,readSize;
  cin>>mailNum;
  object* list[readinSize]={nullptr};
  for(int i=0;i<readSize;i++){
    string type;
    cin>>type;
    string _contain_,_postmark_;
    date send_d,arrive_d;
    cin>>_contain_>>_postmark_>>send_d>>arrive_d;
    if(type=="air"){
      date take_off,land;
      string airline;
      cin>>take_off>>land>>airline;
      list[i]=new air_mail(_contain_,_postmark_,send_d,arrive_d,take_off,land,airline);
    }else if(type=="train"){
      int station_num;
      cin>>station_num;
      string* sname;
      date* stime;
      sname=new string[station_num];
      stime=new date[station_num];
      for(int j=0;j<station_num;j++)
        cin>>sname[j]>>stime[j];
      list[i]=new train_mail(_contain_,_postmark_,send_d,arrive_d,sname,stime,station_num);
      delete []sname;
      delete []stime;
    }else if(type=="car"){
      int mile;
      string driver;
      cin>>mile>>driver;
      list[i]=new car_mail(_contain_,_postmark_,send_d,arrive_d,mile,driver);
    }else if(type=="no"){
      list[i]=new mail(_contain_,_postmark_,send_d,arrive_d);
    }
  }
  int queryOp;
  int id;
  while(cin>>queryOp){
    cin>>id;
    // !following is an example:
    if(queryOp==0){
      cout<<list[id]->type()<<endl;
    }else if(queryOp==1){
      list[id]->print();
    }else if(queryOp==2){
      int y,m,d;
      cin>>y>>m>>d;
      cout<<list[id]->send_status(y,m,d)<<endl;
    }else if(queryOp==3){
      int other;
      cin>>other;
      obj_swap(list[id],list[other]);
    }else if(queryOp==4){
      //example
      object* tmp;
      obj_copy(list[id],tmp);
      delete list[id];
      obj_copy(tmp,list[id]);
      delete tmp;
    }
    // !example code finish
  }
  delete []list;
  return 0;
}
