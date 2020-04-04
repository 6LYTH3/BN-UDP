## Start Bylnk Server

`sudo docker run -d --restart=always --name blynk-server -v $HOME/blynk-data:/data -p 8080:8080 -p 9443:9443 mpherg/blynk-server`