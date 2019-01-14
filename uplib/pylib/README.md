# uplib--pylib

---
### 1.1 pydraw
#### 1.1.1 pyplot_zh.py
@Description: Solve messy code when using matplotlib

```
help_me()

@function: Print solve methods
```

---
### 2 pyprint
#### 2.1 special_string.py
@Description: Some special string for print

```
split_line(keywords="")

@function: special split line for print
:param keywords: key description
```

---
### 3 pycv
#### 3.1 video_process.py
@Description: Using opencv to get video's frame
```
video_capture(video_path, save_path)

@function: 读取视频并取帧
:param video_path: 
:param save_path:
:return: 
```

---
### 4 pyfiles
#### 4.1 files_operate.py
@Description: Files or directory operation
```
get_files_by_suffix(file_path, suffix='.jpg')

@function: Get files by suffix
:param file_path: directory including files
:param suffix: if suffix == ".*", return all files
:return: file lists satisfied suffix requirement


delete_by_requirement(dir_path, requirement="*")

@function: Delete file or directory by requirements
:param dir_path: directory path
:param requirement: file name or directory name, if requirement == "*", delete all files and directory
:return: None
```

---
### 5 pylogs
#### 5.1 print_log.py
@Description: Let print output to log file
```
print_to_file(log_file)

@function: Setting print to log file
:param log_file: print information is stored in this log_file
:return: None


logs_msg(py_file, log_line, info)

@function: Special format message to trace error
:param py_file: happening error's python file
:param log_line: happening error's line
:param info: some notes to explain why happening error
:return: msg


logging_help()

@function: Give information for logging using


get_current_time()

@function: Get current time
:return: current time


split_line(keywords="")

@function: special split line for print
:param keywords: key description
:return: None
```

---
## 6 pytime
### 6.1 get_time.py
@Description: Get current time
```
get_current_time()

@function: 获取系统本地时间
:return:
```