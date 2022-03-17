import functools
import os

from matplotlib import gridspec
import matplotlib.pylab as plt
import numpy as np
import tensorflow as tf
import tensorflow_hub as hub

print("TF Version: ", tf.__version__)
print("TF-Hub version: ", hub.__version__)
print("Eager mode enabled: ", tf.executing_eagerly())
print("GPU available: ", tf.test.is_gpu_available())

def crop_center(image):
  """Returns a cropped square image."""
  shape = image.shape
  new_shape = min(shape[1], shape[2])
  offset_y = max(shape[1] - shape[2], 0) // 2
  offset_x = max(shape[2] - shape[1], 0) // 2
  image = tf.image.crop_to_bounding_box(
      image, offset_y, offset_x, new_shape, new_shape)
  return image

@functools.lru_cache(maxsize=None)
def load_image(image_url, image_size=(256, 256), preserve_aspect_ratio=True):
  """Loads and preprocesses images."""
  image_path = tf.keras.utils.get_file(os.path.basename(image_url)[-128:], image_url)
  img = plt.imread(image_path).astype(np.float32)[np.newaxis, ...]
  if img.max() > 1.0:
    img = img / 255.
  if len(img.shape) == 3:
    img = tf.stack([img, img, img], axis=-1)
  img = crop_center(img)
  img = tf.image.resize(img, image_size, preserve_aspect_ratio=True)
  return img

def show_n(images, titles=('',)):
  n = len(images)
  image_sizes = [image.shape[1] for image in images]
  w = (image_sizes[0] * 6) // 320
  plt.figure(figsize=(w  * n, w))
  gs = gridspec.GridSpec(1, n, width_ratios=image_sizes)
  for i in range(n):
    plt.subplot(gs[i])
    plt.imshow(images[i][0], aspect='equal')
    plt.axis('off')
    plt.title(titles[i] if len(titles) > i else '')
    plt.savefig('./test1.jpg')
  plt.show()

hub_handle = 'https://tfhub.dev/google/magenta/arbitrary-image-stylization-v1-256/2'
hub_module = hub.load(hub_handle)



content_urls = dict(
  dog='https://guanghanwu.github.io/CCI_CodingTwo_4Labs/LabFourAIArt/OriginalImages/cuteDog.jpg',
  cheetah='https://guanghanwu.github.io/CCI_CodingTwo_4Labs/LabFourAIArt/OriginalImages/cheetah.jpg',
  )
style_urls = dict(
  metalFoil='https://guanghanwu.github.io/CCI_CodingTwo_4Labs/LabFourAIArt/OriginalImages/metalFoil.jpg',
  root='https://guanghanwu.github.io/CCI_CodingTwo_4Labs/LabFourAIArt/OriginalImages/root.jpg',
  smoothFur='https://guanghanwu.github.io/CCI_CodingTwo_4Labs/LabFourAIArt/OriginalImages/smoothFur.jpg',
  whiteLineDarkSpace='https://guanghanwu.github.io/CCI_CodingTwo_4Labs/LabFourAIArt/OriginalImages/whiteLineDarkSpace.jpg',
  fire='https://guanghanwu.github.io/CCI_CodingTwo_4Labs/LabFourAIArt/OriginalImages/fire2.jpg',

)

content_image_size = 700
style_image_size = 256
content_images = {k: load_image(v, (content_image_size, content_image_size)) for k, v in content_urls.items()}
style_images = {k: load_image(v, (style_image_size, style_image_size)) for k, v in style_urls.items()}
style_images = {k: tf.nn.avg_pool(style_image, ksize=[3,3], strides=[1,1], padding='SAME') for k, style_image in style_images.items()}


content_name = 'dog'  # @param ['dog', 'cheetah']
style_name = 'root'  # @param ['metalFoil', 'root', 'smoothFur', 'whiteLineDarkSpace', 'fire']
stylized_image = hub_module(tf.constant(content_images[content_name]),
                            tf.constant(style_images[style_name]))[0]
show_n([content_images[content_name], style_images[style_name], stylized_image],
       titles=['Original content image', 'Style image', 'Stylized image'])

content_name = 'cheetah'
style_name = 'smoothFur'
stylized_image = hub_module(tf.constant(content_images[content_name]),
                            tf.constant(style_images[style_name]))[0]
show_n([content_images[content_name],style_images[style_name],stylized_image],
       titles=['Original content image', 'Style image', 'Stylized image'])
#
#
style_name = 'fire'
stylized_image = hub_module(tf.constant(content_images[content_name]),
                            tf.constant(style_images[style_name]))[0]
show_n([content_images[content_name],style_images[style_name],stylized_image],
       titles=['Original content image', 'Style image', 'Stylized image'])
