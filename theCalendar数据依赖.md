# TheCalendar类数据依赖
目前我希望可以实现的功能：
- 点击周一到周日的按钮，显示当天都完成了哪些计划
- 在“查看我的日历”中点击某日，显示当日完成的计划
**目前有两套方案实现这一点：**
1. 在“每日计划”窗口直接复现
2. 新弹出一个窗口（这样可能代码重复量就会比较大了，倾向于前者）
因此大概的逻辑就是，我在TheCalendar类里面写好按钮交互，按钮能够直接控制“DailyPlan"部分的$show$函数去调用对应的内容；与此同时我们便应该实现一个直接回到当日的途径。
# ddlReminder类数据依赖
这部分具体依赖于“Longtermproject"类的实现方式。
我认为可以通过提供的接口，获得某个project大项的截止日期并且更新到这个ddl中，更细节的部分就不用了
# dailyplan类提供的函数：
## 给longtermproject
一个add函数，可以调用某一天的该函数从而将计划加入当天并进行显示
## 给thecalendar
每一个dailyplan只负责一天的事情，建议thercalendar定义一个dailyplan的数组
dailyplan中的ui会显示当日的事件
