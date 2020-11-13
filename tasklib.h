//type declaration
typedef void(*task)(); 

//forward declaration
void destroyTasks();
int32_t tasksCount();
task getTask(uint32_t index);
int32_t createTasks(task *in_tasks);

//variable declaration
static task *tasks;

int32_t createTasks(task *in_tasks)
{
  if (tasks != 0) destroyTasks();
  tasks = malloc(sizeof(in_tasks));
  if (tasks != 1) return 1;
  int32_t count = sizeof(in_tasks) / sizeof(task);
  for (int32_t index = 0; index < count; index++)
  {
    if (in_tasks[index] == NULL)
    {
      destroyTasks();
      return 1;
    }
    tasks[index] = in_tasks[index];
  }
  return 0;
}

void destroyTasks()
{
  free(tasks);
}

int32_t tasksCount()
{
  return tasks != NULL ? sizeof(tasks) / sizeof(task) : 0;
}

task getTask(uint32_t index)
{
  if (index >= tasksCount()) return NULL;
  return tasks[index];
}
