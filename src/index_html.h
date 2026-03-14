const char* indexHtml =
"<!doctype html>"
"<html lang='en'>"
"<head>"
"<meta charset='UTF-8'>"
"<title>ESP OTA Update</title>"

"<style>"
"body{font-family:Verdana,sans-serif;font-size:14px;}"
".ota-container{width:400px;padding:20px;margin:20px auto;border:2px solid #e0e0e0;border-radius:10px;}"
".ota-title{text-align:center;font-size:18px;font-weight:bold;margin-bottom:12px;}"
".ota-form{margin-bottom:10px;}"
".update-button{float:right;}"
".progress-container{width:100%;height:24px;background:#e0e0e0;border-radius:8px;position:relative;overflow:hidden;}"
".progress-bar{width:0%;height:100%;background:#2196f3;border-radius:8px;}"
".progress-success{background-color:#04aa6d!important;}"
".progress-text{position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);color:white;font-weight:bold;pointer-events:none;}"
".status-message{margin-top:12px;text-align:center;font-weight:bold;}"
"</style>"
"</head>"

"<body>"
"<div class='ota-container'>"
"<div class='ota-title'>ESP 2S OTA</div>"

"<form id='upload-form' class='ota-form' method='POST' enctype='multipart/form-data'>"
"<input type='file' name='update' accept='.bin' required>"
"<input type='submit' value='Update' class='update-button'>"
"</form>"

"<div class='progress-container'>"
"<div id='progress-bar' class='progress-bar'></div>"
"<div id='progress-text' class='progress-text'>0%</div>"
"</div>"

"<div id='status' class='status-message'></div>"
"</div>"

"<script>"
"const form=document.getElementById('upload-form');"
"const progressBar=document.getElementById('progress-bar');"
"const progressText=document.getElementById('progress-text');"
"const status=document.getElementById('status');"
"const submitBtn=form.querySelector(\"input[type='submit']\");"

"form.addEventListener('submit',e=>{"
"e.preventDefault();"

"const file=form.update.files[0];"
"if(!file||!file.name.endsWith('.bin')){"
"alert('Please select a valid .bin firmware file');"
"return;"
"}"

"progressBar.classList.remove('progress-success');"
"progressBar.style.width='0%';"
"progressText.innerText='0%';"
"status.innerText='';"

"Array.from(form.elements).forEach(el=>{el.disabled=true;});"

"const data=new FormData(form);"
"const req=new XMLHttpRequest();"

"req.open('POST','/update');"

"req.upload.addEventListener('progress',p=>{"
"if(!p.lengthComputable)return;"
"const percent=Math.round((p.loaded/p.total)*100);"
"const width=percent+'%';"

"progressBar.style.width=width;"
"progressText.innerText=width;"

"if(percent===100){"
"progressBar.classList.add('progress-success');"
"status.innerText='Upload complete. Device rebooting...';"
"waitForDevice();"
"}"
"});"

"req.onerror=()=>{"
"alert('Upload failed');"
"Array.from(form.elements).forEach(el=>{el.disabled=false;});"
"};"

"req.send(data);"
"});"

"function waitForDevice(){"
"const interval=setInterval(()=>{"
"fetch('/',{cache:'no-store'})"
".then(()=>{"
"clearInterval(interval);"
"status.innerText='Device updated successfully ✓';"
"progressText.innerText='100%';"
"Array.from(form.elements).forEach(el=>{el.disabled=false;});"
"})"
".catch(()=>{});"
"},2000);"
"}"
"</script>"

"</body>"
"</html>";