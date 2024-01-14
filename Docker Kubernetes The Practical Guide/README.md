# Udemy.Docker-Kubernetes-The-Practical-Guide
Docker &amp; Kubernetes: The Practical Guide https://www.udemy.com/course/docker-kubernetes-the-practical-guide

## Commands

```bash
# Build image
docker build .

# Run container. Create a new one. Block console. Flag -d detach 
docker run -p 3000:3000 272b00b5a43909e8eac98ca4475358abbdcd0a7ed367fce84d52dfe3cbe73adf

# Show running containers
docker ps

# Stop container
docker stop trusting_mahavira

# Start existing container. Not block console (run in background). Flag -a in attach mode
docker start nice_matsumoto

# Attach to the existing container
docker attach nice_matsumoto

# Print all logs
docker logs nice_matsumoto

# Print all logs in interactive mode
docker logs -f nice_matsumoto

# Run container with Allocate a pseudo-TTY and Keep STDIN open even if not attached
# We can use STDIN for intaraction
docker run -it a5dd

# Start a exisiting container in interctive mode
docker start -a -i zen_jackson

# Remove a few containers
docker rm zen_jackson peaceful_ride nice_matsumoto trusting_mahavira hungry_bartik

# Remove all containers
docker container prune

# Remove all images
docker image prune -a

# Remove one image
docker rmi a5dded830698

# Run container. Automatically remove the container when it exits
docker run --rm a5dd

# Inspect image properties
docker image inspect a5dded830698

# Copy files TO a container
docker cp dummy/. goofy_chandrasekhar:/test

# Copy files FROM a container
docker cp goofy_chandrasekhar:/test dummy

# Set name for a conatiner
docker run -p 3000:80 --name node_container 2660739ff4177776dd87f66f5df2d6087d9782ade6afcb37a18ad505a36c9cc9

# Set tag for an image 
docker build -t nodejs-app:1.0 .

# Retag image
docker tag node-demo:latest academind/node-hello-world

# Access to DockerHub login/logout
docker login
docker logout

# Push image to DockerHub
docker build -t matsuk/image-for-ira .
docker push matsuk/image-for-ira

# Show list of volumes
docker volume ls

# Create named permanent volume 
docker run -p 3000:80 -d --name feedback-app --rm -v feedback:/app/feedback feedback-node:volumes

# Remove volume
docker volume rm VOL_NAME

# Remove all volumes
docker volume prune

# Anonymous Volume
docker run -v /app/data ...
# Named Volume
docker run -v data:/app/data ...
# Bind Mount
docker run -v /path/to/code:/app/data ...

# Bind mount
docker run -p 3000:80 -d --name feedback-app --rm -v feedback:/app/feedback -v "D:\Repositories\github.com\Udemy.Docker-Kubernetes-The-Practical-Guide\data-volumes-01-starting-setup:/app" feedback-node:volumes
# OR
docker run -p 3000:80 -d --name feedback-app -v feedback:/app/feedback -v "%cd%":/app feedback-node:volumes

# Set env variable from command line
docker run -p 3000:80 --env PORT=8000 -d --name feedback-app -v feedback:/app/feedback -v "%cd%":/app -v /app/node_modules feedback-node:env

# Set env variable from env file
docker run -p 3000:80 --env-file ./.env PORT=8000 -d --name feedback-app -v feedback:/app/feedback -v "%cd%":/app -v /app/node_modules feedback-node:env

# Set args via command line
docker build -t feedback-node:arg --build-arg DEFAULT_PORT=8000 .
```
